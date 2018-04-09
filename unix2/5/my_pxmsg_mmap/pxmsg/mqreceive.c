#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include "mqueue.h"

int main(int argc, char **argv)
{
    int c, flags;
    mqd_t mqd;
    ssize_t n;
    uint32_t prio;
    void *buff;
    struct mq_attr attr;

    flags = O_RDONLY;
    while((c = getopt(argc, argv, "n")) != -1)
    {
        switch(c)
        {
            case 'n':
                flags |= O_NONBLOCK;
                break;
        }
    }

    if(optind != argc - 1)
    {
        printf("usage: mgreceive [-n] <name>\n");
        exit(0);
    }

    mqd = mq_open(argv[optind], flags);
    mq_getattr(mqd, &attr);

    buff = malloc(attr.mq_msgsize);
    n = mq_receive(mqd, buff, attr.mq_msgsize, &prio);
    printf("read %ld bytes, priority = %u\n", (long)n, prio);
    exit(0);
}
