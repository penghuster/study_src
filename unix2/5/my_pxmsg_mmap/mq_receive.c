
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "mqueue.h"

ssize_t mq_receive(mqd_t mqd, char *ptr, size_t maxlen, unsigned int* priop)
{
    int n;
    long index;
    int8_t *mptr;
    ssize_t len;
    struct mq_hdr *mqhdr;
    struct mq_attr *attr;
    struct msg_hdr *msghdr;
    struct mq_info *mqinfo;

    mqinfo = mqd;

    if(MQI_MAGIC != mqinfo->mqi_magic)
    {
        errno = EBADF;
        return -1;
    }
    mqhdr = mqinfo->mqi_hdr;
    mptr = (int8_t*)mqhdr;
    attr = & mqhdr->mqh_attr;
    if((n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0)
    {
        errno = n;
        return -1;
    }
    if(maxlen < attr->mq_msgsize)
    {
        errno = EMSGSIZE;
        goto err;
    }

    if(0 == attr->mq_curmsgs)  // queue is empty
    {
        if(mqinfo->mqi_flags & O_NONBLOCK)
        {
            errno = EAGAIN;
            goto err;
        }

        mqhdr->mqh_nwait++;
        while(0 == attr->mq_curmsgs)
            pthread_cond_wait(&mqhdr->mqh_wait, &mqhdr->mqh_lock);
        mqhdr->mqh_nwait--;
    }

    if((index = mqhdr->mqh_head) == 0)
    {
        printf("mq_receive: curmsgs = %ld; head = 0", attr->mq_curmsgs);
    }

    msghdr = (struct msg_hdr*)&mptr[index];
    mqhdr->mqh_head = msghdr->msg_next;
    len = msghdr->msg_len;
    memcpy(ptr, msghdr + 1, len); //copy the message itself 
    if(NULL != priop)
        *priop = msghdr->msg_prio;

    //just-read messge goes to front of free list 
    msghdr->msg_next = mqhdr->mqh_free;
    mqhdr->mqh_free = index;

    //wake up anyone blocked in mq_send waiting for room 
    if(attr->mq_curmsgs == attr->mq_maxmsg)
        pthread_cond_signal(&mqhdr->mqh_wait);
    attr->mq_curmsgs--;

    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return len;

err:
    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return -1;

}
