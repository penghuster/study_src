#include "mqueue.h"
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    mqd_t mqd;
    struct mq_attr attr;

    if(2 != argc)
    {
        printf("usage: mqgetattr <name>");
        exit(0);
    }

    mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);
    if(-1 == mqd)
    {
        printf("Failed to open %s, error(%s).\n", argv[1], strerror(errno));
        exit(0);
    }

    int ret = mq_getattr(mqd, &attr);
    if(-1 == ret)
    {
        printf("Failed to call mggetattr\n");
    }

    printf("max #msg = %ld, max #bytes/msg = %ld, "
            "#currently on queue = %ld\n",
            attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    ret = mq_close(mqd);
    if(0 != ret)
    {
        printf("Failed to call mq_close, error(%s).\n", strerror(errno));
    }
    exit(0);
}
