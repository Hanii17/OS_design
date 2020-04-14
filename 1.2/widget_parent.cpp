#include "widget_parent.h"
#include "ui_widget_parent.h"

Widget_parent::Widget_parent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_parent)
{
    ui->setupUi(this);

    int pid=getpid();
    ui->label_pidinput->setText(QString::number(pid));//显示进程id
    semid=semget(key1,2,IPC_CREAT|0666);//创建信号灯集，只有2个信号灯，键值为0

       ui->label_semid_input->setText(QString::number(semid));
      semun arg;
      arg.val=Buffer_num;
      semctl(semid,0,SETVAL,arg);//对0号信号灯赋值1，表示是否有空
      arg.val=0;
      semctl(semid,1,SETVAL,arg);//对1号信号灯赋值0，表示是否有数

      //创建共享主存组

      for(int i=0;i<Buffer_num;i++){
       myshm_id[i]=shmget(key2+i,sizeof(struct buffer),IPC_CREAT|0666);

        share_memry[i]=(struct buffer*)shmat(myshm_id[i],NULL,0);//共享内存映射，返回指向该共享内存的指针
        share_memry[i]->end=0;
  }
      ui->label_share_memry_input->setText(QString::number((uintptr_t)share_memry,16));


}

Widget_parent::~Widget_parent()
{
    delete ui;
    for(int i=0;i<Buffer_num;i++){
       shmctl(myshm_id[i],IPC_RMID,0);//删除共享内存
       }
     //删除信号灯集
     semctl(semid,0,IPC_RMID);
}




