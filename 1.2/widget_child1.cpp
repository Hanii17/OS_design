#include "widget_child1.h"
#include "ui_widget_child1.h"
#include<QDebug>
#include<QTextStream>
widget_child1::widget_child1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_child1)
{
    ui->setupUi(this);
   this->status=false;
    int pid=getpid();
    ui->label_2->setText(QString::number(pid));//显示进程id
    semid=semget(key1,2,IPC_CREAT|0666);//创建信号灯集，只有2个信号灯，键值为0
    int myshm_id[Buffer_num];
    for(int i=0;i<Buffer_num;i++){
     myshm_id[i]=shmget(key2+i,sizeof(struct buffer),IPC_CREAT|0666);
      share_memry[i]=(struct buffer*)shmat(myshm_id[i],NULL,0);//共享内存映射，返回指向该共享内存的指针
      share_memry[i]->end=0;}
    connect(this,&widget_child1::display,this,&widget_child1::deal_display);

}

widget_child1::~widget_child1()
{
    delete ui;
}


void widget_child1::start_read()
{
    filein=fopen(pathname,"rb");
    if(NULL==filein)
    {
        QMessageBox::about(this,"Error","file open error!Process will be finished in 3s");
         sleep(2);
        exit(-1);
    }

    int j=0;
    while(1)
    {
     P(semid,0);
     file_end=fread(share_memry[j]->buf,sizeof(char),Buffer_size,filein);
       if(file_end<=0)//读结束
       {
          share_memry[j]->end=file_end;
          V(semid,1);
          fclose(filein);
          return ;
       }
       share_memry[j]->end=file_end;
       //s=s+"read "+QString::number(file_end)+"from file "+QString(QLatin1String(pathname))+"\n";
       s="read "+QString::number(file_end)+" from file "+QString(QLatin1String(pathname));
       emit display();
       // this->ui->textBrowser->append(s);
       //qDebug()<<"read "+QString::number(file_end)+" from file "+QString(QLatin1String(pathname));
       j=(j+1)%Buffer_num;
       V(semid,1);
    }


}



void widget_child1::on_pushButton_2_clicked()
{

   QByteArray pn=this->ui->lineEdit_filename->text().toLatin1();
  // pathname=pn.data();
   qDebug()<<pn;
   pathname=pa;
   if(pathname==nullptr)
   {
       QMessageBox::about(this,"error","please input a file name first");
   }
   else
   {
       QMessageBox::about(this,"1",QString::fromLatin1(pathname));
           status=true;
   }
}

void widget_child1::on_pushButton_clicked()
{
    if(status)
    {
        status=false;
        this->start_read();

    }
    else
    {
      QMessageBox::about(this,"Error","Read has already start!");
    }
}

void widget_child1::deal_display()
{
    this->ui->textBrowser->append(s);

}
