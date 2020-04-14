#ifndef PRAMA_H
#define PRAMA_H
#include<sys/types.h>
#include<sys/sem.h>
#include<wait.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdio.h>
#include<signal.h>

const int SIG_CHILD2_OK =__SIGRTMIN+10;
const int SIG_CHILD1_OK =__SIGRTMIN+13;
const key_t key1=5569;
const key_t key2=5572;
const int Buffer_num=8;
const int Buffer_size=128;
union semun {
               int              val;    /* cmd=SETVAL时使用 */
               struct semid_ds *buf;    /* cmd=IPC_STAT、 IPC_SET时使用 */
               unsigned short  *array;  /* cmd= GETALL、 SETALL时使用 */
               struct seminfo  *__buf;  /* cmd=IPC_INFO (Linux-specific) 时使用*/
           };
//共享内存缓冲区
struct buffer{
    int end;
    char buf[Buffer_size];
};
//P操作
static void P(int semid,int index)
{
    struct sembuf sem;
    sem.sem_num=index;//信号量标识
    sem.sem_op=-1;   //P操作进行减1
    sem.sem_flg=0;
    semop(semid,&sem,1);//只对这一个信号灯进行操作
    return ;

}

static void V(int semid,int index)
{
  struct sembuf sem;
    sem.sem_num=index;//信号量标识
    sem.sem_op=1;   //V操作进行加1
    sem.sem_flg=0;
    semop(semid,&sem,1);//只对这一个信号灯进行操作
    return ;
}
#endif // PRAMA_H
