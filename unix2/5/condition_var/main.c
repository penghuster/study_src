#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct msg
{
    struct msg *m_next;
    int i;
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg()
{
    struct msg *mp;
    while(1)
    {
        pthread_mutex_lock(&qlock);
        while(NULL == workq)
        {
            printf("before wait\n");
            pthread_cond_wait(&qready, &qlock);
            printf("after wait\n");
        }

        printf("hello\n");

        mp = workq;
        workq = mp->m_next;
        pthread_mutex_unlock(&qlock);
    }
}

void enqueue_msg(struct msg *mp)
{
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    sleep(1);
    printf("-----\n");
    pthread_cond_signal(&qready);
}

void *doing(void *arg)
{
    process_msg();
}


void* test(void *arg)
{
    struct msg mg;
    mg.m_next = NULL;
    enqueue_msg(&mg);
}

int main()
{

    struct msg m1, m2;
    m1.m_next = NULL;
    m1.i = 2;

    m2 = m1;

    printf("i1 = %d; i2 =%d\n", m1.i, m2.i);
    return 0;
    pthread_t t1, t2;
    pthread_create(&t1, NULL, doing, NULL);
    sleep(1);
    pthread_create(&t2, NULL, test, NULL);


    while(1)
    {
        sleep(1);
    }
}
