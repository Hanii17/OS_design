#include "widget_child2.h"
#include "ui_widget_child2.h"

widget_child2::widget_child2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_child2)
{
    ui->setupUi(this);
    int pid=getpid();
    ui->label_2->setText(QString::number(pid));//显示进程id
     semid=semget(key1,2,IPC_CREAT|0666);//创建信号灯集，只有2个信号灯，键值为0
     //创建共享主存组
        int myshm_id[Buffer_num];
        for(int i=0;i<Buffer_num;i++){
         myshm_id[i]=shmget(key2+i,sizeof(struct buffer),IPC_CREAT|0666);
          share_memry[i]=(struct buffer*)shmat(myshm_id[i],NULL,0);//共享内存映射，返回指向该共享内存的指针
          share_memry[i]->end=0;
    }
        status=false;
 pathname1=pa2;






}

widget_child2::~widget_child2()
{
    delete ui;
}
void widget_child2::start_write()
{
    fileout=fopen(pathname1,"wb");
      if(NULL==fileout)
      {

          QMessageBox::about(this,"Error","file open error!Process will be finished in 3s");
           sleep(2);
          exit(-1);

      }
      int k=0;
      while(1)
      {
       P(semid,1);
       fwrite(share_memry[k]->buf,sizeof(char),share_memry[k]->end,fileout);

       this->ui->textBrowser->append("write "+QString::number(share_memry[k]->end)+" to file "+QString(QLatin1String(pathname1)));

       if(share_memry[k]->end==0)
       {
           fclose(fileout);
           return ;
       }
       k=(k+1)%Buffer_num;
       V(semid,0);

      }

}

void widget_child2::on_pushButton_clicked()
{
    QByteArray pn1=ui->lineEdit_copyfilename->text().toLatin1();
    //pathname1=pn1.data();
    if(pathname1!=nullptr)
    {
        status=true;
        QMessageBox::about(this,"1",QString::fromLatin1(pathname1));
    }
   if(status)
   {
       status=false;
       this->start_write();
   }
   else
   {
       QMessageBox::about(this,"Error","write has already start or start without a pathname");
   }
}
