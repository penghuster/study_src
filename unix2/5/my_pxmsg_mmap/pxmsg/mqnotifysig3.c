#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mqueue.h"
#include <signal.h>
#include <fcntl.h>

volatile sig_atomic_t mqflag; //set nonzero by signal handler 
static void sig_usr1(int);

int main(int argc, char **argv)
{
    mqd_t mqd;
    void *buff;
    ssize_t n;
    sigset_t zeromask, newmask, oldmask;
    struct mq_attr attr;
    struct sigevent sigev;
    if(2 != argc)
    {
        printf("usage: mqnotifysig3 <name>\n");
        exit(0);
    }

    mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);
    if(-1 == mqd)
    {
        printf("failed to call mq_open, error(%s).\n", strerror(errno));
        exit(0);
    }

    int ret = mq_getattr(mqd, &attr);
    if(-1 == ret)
    {
        printf("Failed to call mq_getattr, error(%s).\n", strerror(errno));
        exit(0);
    }


    buff = malloc(attr.mq_msgsize);

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigemptyset(&oldmask);

    sigaddset(&newmask, SIGUSR1);

    //establish signal hander, enable notification 
    signal(SIGUSR1, sig_usr1);

    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;

    ret = mq_notify(mqd, &sigev);
    if(-1 == ret)
    {
        printf("Failed to call mq_notify, error(%s).\n", strerror(errno));
        exit(0);
    }

    for( ; ; )
    {
        //block  SIGUSR1，以使判断 flag值得时候其值不会改变
        sigprocmask(SIG_BLOCK, &newmask, &oldmask); //block SIGUSR1
        while(0 == mqflag)
        {
            //阻塞，直到任意一个信号发生唤醒
            sigsuspend(&zeromask);
        }
        mqflag = 0; //reset flag 

        mq_notify(mqd, &sigev); //再次注册，必须在取消息之前

        //确保接收完消息队列中的消息直到为空
        while((n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) > 0)
        {
            printf("read %ld bytes\n", (long)n);
        }

        if(EAGAIN != errno)//过滤因消息队列为空，返回的错误码 
        {
            printf("mq_receive error, error(%s)\n", strerror(errno));
        }

        //sigprocmask(SIG_UNBLOCK, &newmask, NULL); //unblock SIGUSR1
    }
    exit(0);
}


static void sig_usr1(int signo)
{
    mqflag = 1;
    return;
}
