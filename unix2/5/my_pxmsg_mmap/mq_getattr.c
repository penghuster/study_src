//#include <syt/type.h>
#include <errno.h>
#include "mqueue.h"

int mq_getattr(mqd_t mqd, struct mq_attr *mqstat)
{
    int n;
    struct mq_hdr *mqhdr;
    struct mq_attr *attr;
    struct mq_info *mqinfo;

    mqinfo = mqd;
    if(MQI_MAGIC != mqinfo->mqi_magic)
    {
        errno  = EBADF;
        return -1;
    }

    mqhdr = mqinfo->mqi_hdr;
    attr = &(mqhdr->mqh_attr);
    if((n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0 )
    {
        errno = n;
        return -1;
    }

    mqstat->mq_flags = mqinfo->mqi_flags;
    mqstat->mq_maxmsg = attr->mq_maxmsg;
    mqstat->mq_msgsize = attr->mq_msgsize;
    mqstat->mq_curmsgs = attr->mq_curmsgs;

    pthread_mutex_unlock(&mqhdr->mqh_lock);
    return 0;

}
