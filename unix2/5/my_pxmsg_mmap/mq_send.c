
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "mqueue.h"

int mq_send(mqd_t mqd, const char *ptr, size_t len, unsigned int prio)
{
    int n;
    long index, freeindex;
    int8_t *mptr;
    struct sigevent * sigev;
    struct mq_hdr *mqhdr;
    struct mq_attr *attr;
    struct msg_hdr *msghdr, *nmsghdr, *pmsghsr;
    struct mq_info *mqinfo;

    mqinfo = mqd;
    if(MQI_MAGIC != mqinfo->mqi_magic)
    {
        errno = EBADF;
        return -1;
    }

    mqhdr = mqinfo->mqi_hdr;
    mptr = (int8_t*)mqhdr; //byter pointer 
    attr = &mqhdr->mqh_attr;
    if((n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0)
    {
        errno = n;
        return -1;
    }

    if(len > attr->mq_msgsize)
    {
        errno = EMSGSIZE;
        goto err;
    }

    if(0 == attr->mq_curmsgs)
    {
        if(0 != mqhdr->mqh_pid && 0 == mqhdr->mqh_nwait)
        {
            sigev = &mqhdr->mqh_event;
            if(SIGEV_SIGNAL == sigev->sigev_notify)
            {
                sigqueue(mqhdr->mqh_pid, sigev->sigev_signo, sigev->sigev_value);
            }
            mqhdr->mqh_pid = 0; //unregister
        }
    }
    else if(attr->mq_curmsgs >= attr->mq_maxmsg)
    {
        //queue is full
        if(mqinfo->mqi_flags & O_NONBLOCK)
        {
            errno = EAGAIN;
            goto err;
        }

        //wait for root for one message on the queue 
        while(attr->mq_curmsgs >= attr->mq_maxmsg)
            pthread_cond_wait(&mqhdr->mqh_wait, &mqhdr->mqh_lock);

    }

    //到达此处 消息列表已经不可能为空，且必定存在至少一个空闲位置
    if( (freeindex = mqhdr->mqh_free) == 0)
    {
        printf("mq_send: curmsgs = %ld; free = 0.\n", attr->mq_curmsgs);
        abort();
    }
    nmsghdr = (struct msg_hdr*)&mptr[freeindex];
    nmsghdr->msg_prio = prio;
    nmsghdr->msg_len = len;
    memcpy(nmsghdr + 1, ptr, len); //copy message from caller 
    mqhdr->mqh_free = nmsghdr->msg_next;; //new freelist head 

    //find right place for message in linked list
    index = mqhdr->mqh_head;
    pmsghsr = (struct msg_hdr*) &(mqhdr->mqh_head); //????????????
    while(index != 0)
    {
        msghdr = (struct msg_hdr*) &mptr[index];
        if(prio > msghdr->msg_prio)
        {
            nmsghdr->msg_next = index;
            pmsghsr->msg_next = freeindex;
            break;
        }
        index = msghdr->msg_next;
        pmsghsr = msghdr;
    }
    if(0 == index)
    {
        //queue was empty or new goes at end of list 
        pmsghsr->msg_next = freeindex;
        nmsghdr->msg_next = 0;
    }

    //wake up anyone blocked in mq_receive waiting for a message
    if(0 == attr->mq_curmsgs)
        pthread_cond_signal(&mqhdr->mqh_wait);
    attr->mq_curmsgs++;

    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return 0;

err:
    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return -1;
}
