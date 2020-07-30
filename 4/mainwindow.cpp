#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"pid"<<"name"<<"stat"<<"priority"<<"memory occpuied");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   QHeaderView *header = ui->tableWidget->verticalHeader();
   header->setHidden(true);
  if_monitor=true;
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
   timer=new QTimer();
   connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
   timer->start(3000);
   showSysInfo();
   showprocess();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSysInfo()
{
    QString buf;
    QFile f("/proc/version");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
        return;

       buf=f.readLine();
       qDebug()<<buf<<"\n";


   int from=buf.indexOf("Linux version");
   int end=buf.indexOf("(");
   QString linux_version(buf.mid(from+14,end-from-15));
    qDebug()<<linux_version;
    from=buf.indexOf("gcc");
    end=buf.indexOf("#");
    QString gcc_version(buf.mid(from+11,end-from-13));
    qDebug()<<gcc_version;
    this->ui->label_GCC->setText(gcc_version);
    this->ui->label_os_version->setText(linux_version);
    this->ui->label_os_type->setText("Linux");
    f.close();

    QFile f1("/proc/cpuinfo");
    if(!f1.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QString buf2[10];
     int i=0;
    while(i<10){
    buf2[i]=f1.readLine();
  qDebug()<<buf2[i]<<"\n";
    i++;}
    from=buf2[1].indexOf("vendor_id");
    end=buf2[1].length();
   QString cpu_id(buf2[1].mid(from+12,end-from-13));
   qDebug()<<cpu_id;
   from=buf2[4].indexOf("model name");
   end=buf2[4].length();
   QString cpu_name(buf2[4].mid(from+13,end-from-13));
   qDebug()<<cpu_name;
   from=buf2[7].indexOf("cpu MHZ");
   end=buf2[7].length();
   QString cpu_hz(buf2[7].mid(from+12,end-from-13));
   cpu_hz=cpu_hz+"MHZ";
   qDebug()<<cpu_hz;
   from=buf2[8].indexOf("cache size");
   end=buf2[8].length();
   QString cache_size(buf2[8].mid(from+13,end-from-14));
   qDebug()<<cache_size;
   ui->label_cpu_type->setText(cpu_id);
   ui->label_cpu_name->setText(cpu_name);
   ui->label_cpu_fre->setText(cpu_hz);
   ui->label_cache->setText(cache_size);
    f1.close();


}

void MainWindow::showprocess()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    QDir qd("/proc");
    QStringList qslist=qd.entryList();
   bool flag=true;
   QStringList pidsum;
   qDebug()<<qslist.size();
   for(int i=0;i<qslist.size();i++)
   {
       qslist[i].toInt(&flag);
       if(flag)
       {
          pidsum.append(qslist[i]);
       }
   }
   qDebug()<<pidsum.size();
   QStringList buf;
   QString filename;
   for(int j=0;j<pidsum.size();j++)
   {
       filename="/proc/"+pidsum[j]+"/stat";
   QFile f(filename);
   if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
   {
       qDebug()<<"file"<<filename<<"not exist!";
       return;}
    buf.append(f.readLine());
    f.close();
   }
   int count;
  for(int k =0;k<buf.size();k++)
  {
      //process id
      QString p_id=buf[k].section(" ",0,0);
     //process name
      QString p_name_=buf[k].section(" ",1,1);
      QString p_name=p_name_.mid(1,p_name_.length()-2);

      //process state
      QString p_state=buf[k].section(" ",2,2);

      //porcess priority
      QString p_priority=buf[k].section(" ",17,17);

      //process use
      QString p_mem_=buf[k].section(" ",22,22);
      int  t=p_mem_.toInt()/1024;
      QString p_mem=QString::number(t);
     p_mem=p_mem+"KB";
      //show process
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());
      count=ui->tableWidget->rowCount()-1;


      ui->tableWidget->setItem(count,0,new QTableWidgetItem(p_id));
      ui->tableWidget->item(count,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignHCenter);

      ui->tableWidget->setItem(count,1,new QTableWidgetItem(p_name));
      ui->tableWidget->item(count,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignHCenter);

      ui->tableWidget->setItem(count,2,new QTableWidgetItem(p_state));
      ui->tableWidget->item(count,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignHCenter);

      ui->tableWidget->setItem(count,3,new QTableWidgetItem(p_priority));
      ui->tableWidget->item(count,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignHCenter);

      ui->tableWidget->setItem(count,4,new QTableWidgetItem(p_mem));
      ui->tableWidget->item(count,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignHCenter);

  }
    qDebug()<<"count"<<count;


}

void MainWindow::updateMem()
{
    QFile file;

    //mem
    file.setFileName("/proc/meminfo");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QStringList buf;
for(int i=0;i<18;i++){

        buf.append(file.readLine());
}
    int mem_total;
    qDebug()<<buf[0].mid(17,buf[0].length()-17-4);
    qDebug()<<buf[1].mid(17,buf[1].length()-17-4);
    qDebug()<<buf[2].mid(17,buf[2].length()-17-4);
    mem_total=buf[0].mid(17,buf[0].length()-17-4).toInt()/1024;
    int mem_ava=buf[2].mid(17,buf[2].length()-17-4).toInt()/1024;
    int mem_used=mem_total-buf[1].mid(17,buf[1].length()-17-4).toInt()/1024;
    this->ui->label_mem_available->setText(QString::number(mem_ava)+"MB");
    this->ui->label_mem_total->setText(QString::number(mem_total)+"MB");
    ui->label_mem_used->setText(QString::number(mem_used)+"MB");
  ui->progressBar_mem->setValue(mem_used*100/mem_total);
   int swap_total=buf[14].mid(17,buf[14].length()-17-4).toInt()/1024;
   int swap_free=buf[15].mid(17,buf[15].length()-17-4).toInt()/1024;
   int swap_used=swap_total-swap_free;
  ui->label_swap_used->setText(QString::number(swap_used)+"MB");
  ui->label_swap_total->setText(QString::number(swap_total)+"MB");
  ui->label_swap_available->setText(QString::number(swap_free)+"MB");
ui->progressBar_swap->setValue(swap_used*100/swap_total);
file.close();
}

void MainWindow::updateCpu()
{
    QFile file1;

    //CPU
    file1.setFileName("/proc/stat");
    if(!file1.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QString buf1=file1.readLine();
    file1.close();
   QString user1=buf1.section(" ",2,2);
   QString nice1=buf1.section(" ",3,3);
   QString system1=buf1.section(" ",4,4);
   QString idle1=buf1.section(" ",5,5);
   QString iowait1=buf1.section(" ",6,6);
   QString irq1=buf1.section(" ",7,7);
   QString softirq1=buf1.section(" ",8,8);
   long  total1=user1.toLong()+nice1.toLong()+system1.toULong()+idle1.toULong()+
           iowait1.toLong()+irq1.toULong()+softirq1.toULong();
  sleep(1);
   QFile file2;
   //CPU
   file2.setFileName("/proc/stat");
   if(!file2.open(QIODevice::ReadOnly|QIODevice::Text))
       return;
   QString buf2=file2.readLine();
   file2.close();
   QString user2=buf2.section(" ",2,2);
   QString nice2=buf2.section(" ",3,3);
   QString system2=buf2.section(" ",4,4);
   QString idle2=buf2.section(" ",5,5);
   QString iowait2=buf2.section(" ",6,6);
   QString irq2=buf2.section(" ",7,7);
   QString softirq2=buf2.section(" ",8,8);
   long  total2=user2.toLong()+nice2.toLong()+system2.toULong()+idle2.toULong()+
           iowait2.toLong()+irq2.toULong()+softirq2.toULong();

   long total=qAbs(total1-total2);
   long idle=qAbs(idle1.toLong()-idle2.toLong());
   qDebug()<<total;
   qDebug()<<idle;
   qDebug()<<100-100*idle/total;
   ui->progressBar_cpu->setValue(100-100*idle/total);


}

void MainWindow::Update()
{

    updateMem();
    updateCpu();
    showprocess();
}


void MainWindow::on_pushButton_clicked()
{
    if(if_monitor){
    ui->pushButton->setText("start monitor");
    timer->stop();
    if_monitor=false;
    }
    else{
         ui->pushButton->setText("stop monitor");
         timer->start(3000);
         if_monitor=true;
    }

}
