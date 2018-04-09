#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "mqueue.h"

int mq_notify(mqd_t mqd, const struct sigevent *notification)
{
    int n;
    pid_t pid;
    struct mq_hdr *mqhdr;
    struct mq_info *mqinfo;

    mqinfo = mqd;
    if(MQI_MAGIC != mqinfo->mqi_magic)
    {
        errno = EBADF;
        return -1;
    }

    mqhdr = mqinfo->mqi_hdr;
    if((n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0)
    {
        errno = n;
        return -1;
    }

    pid = getpid();
    if(NULL == notification)
    {
        if(mqhdr->mqh_pid == pid)
        {
            mqhdr->mqh_pid = 0; //unregister calling process 
        }
        //no error if caller not regisetered
    }
    else
    {
        if(0 != mqhdr->mqh_pid)
        {
            //kill 函数发送空信号，可以检查进程是否存在，而不发送任何信号，若进程不存在
            //则会返回一个 ESRCH错误； 而如果先前注册过的进程仍然存在，则返回EBUSY错误
            if(kill(mqhdr->mqh_pid, 0) != -1 || errno != ESRCH)
            {
                errno = EBUSY;
                goto err;
            }
        }
        mqhdr->mqh_pid = pid;
        mqhdr->mqh_event = *notification;
    }
    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return 0;

err:
    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return -1;

}
