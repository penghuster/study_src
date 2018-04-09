#include "unpipc.h"

void client(int, int);
void server(int, int);

int main(int argc, char** argv)
{
    int pipe1[2], pipe2[2];
    pid_t childpid;

    int ret = pipe(pipe1); //create two pipes 
    if(-1 == ret)
    {
        printf("ctreate pipe error: %s \n", strerror(errno));
        exit(1);
    }
    ret = pipe(pipe2);
    if(-1 == ret)
    {
        printf("ctreate pipe error: %s \n", strerror(errno));
        exit(1);
    }

    childpid = fork();
    if(-1 == childpid)
    {
        printf("Failed to call fork, error: %s\n", strerror(errno));
        exit(1);
    }

    if(0 == childpid)//子进程 因为父亲是唯一的,可以轻松获取
    {
        if(-1 == close(pipe1[1]) || -1 == close(pipe2[0]))
        {
            printf("Failed to close pipe, error: %s\n", strerror(errno));
            exit(1);
        }
        server(pipe1[0], pipe2[1]);
        exit(0);
    }

    //parent process
    if(-1 == close(pipe1[0]) || -1 == close(pipe2[1]))
    {
            printf("Failed to close pipe, error: %s\n", strerror(errno));
            exit(1);
    }

    client(pipe2[0], pipe1[1]);

    wait

    if((childpid = fork()) == 0)
    {
        close
    }
}
