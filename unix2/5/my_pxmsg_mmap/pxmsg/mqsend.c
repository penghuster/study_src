#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mqueue.h"
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    mqd_t mqd;
    void *ptr;
    size_t len;
    unsigned int  prio;

    if(argc != 4)
    {
        printf("usage: mqsend <name> <#bytes> <priority>\n");
        exit(0);
    }

    len = atoi(argv[2]);
    prio = atoi(argv[3]);

    mqd = mq_open(argv[1], O_WRONLY);
    ptr = calloc(len, sizeof(char));
    if(NULL == ptr)
    {
        printf("Failed to call alloc, error(%s).\n", strerror(errno));
        exit(0);
    }
    memset(ptr, 'a', len);

    int ret = mq_send(mqd, ptr, len, prio);
    if(-1 == ret)
    {
        printf("Failed to call mq_send, error(%s).\n", strerror(errno));
    }
    exit(0);
}
