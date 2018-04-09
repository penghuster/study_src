
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>           /* For O_* constants */ 
#include <error.h>
#include <errno.h>
#include <mqueue.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
//#define FILE_MODE 12

struct mq_attr attr;


int main(int argc, char **argv)
{
    int c, flags;
    mqd_t mqd;
    flags = O_RDWR | O_CREAT | O_NONBLOCK;
    memset(&attr, 0, sizeof(struct mq_attr));
    while(-1 != (c = getopt(argc, argv, "em:z:")))
    {
        switch(c)
        {
        case 'e':
            flags |= O_EXCL;
            break;
        case 'm':
            attr.mq_maxmsg = atol(optarg);
            break;
        case 'z':
            attr.mq_msgsize = atol(optarg);
            break;
        }
    }
    if(optind != argc - 1)
    {
        printf("usage: mqcreate [ -e ] [ -m maxmsg -z msgsize  ] <name>\n");
        exit(0);
    }
    if((0 != attr.mq_maxmsg && 0 == attr.mq_msgsize)||
            (0 == attr.mq_maxmsg && 0 != attr.mq_msgsize))
    {
        printf("must specify both -m maxmsg and -z msgsize\n");
        exit(0);
    }

    mqd = mq_open(argv[optind], flags, FILE_MODE, (0 != attr.mq_maxmsg) ? &attr : NULL);
    //mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
    if(-1 == mqd)
    {
        printf("Failed to call mq_open, error: %s\n", strerror(errno));
        exit(0);
    }

    if(0 != mq_close(mqd))
    {
        printf("Failed to close mq, error: %s\n", strerror(errno));
    }
    exit(0);

}
