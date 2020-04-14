#ifndef WIDGET_CHILD1_H
#define WIDGET_CHILD1_H

#include <QWidget>
#include<prama.h>
#include<QString>
#include<QFileDialog>
#include<QByteArray>
#include<QMessageBox>
#include<QObject>
namespace Ui {
class widget_child1;
}

class widget_child1 : public QWidget
{
    Q_OBJECT

public:
    explicit widget_child1(QWidget *parent = nullptr);
    ~widget_child1();
   void  start_read();



private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
public slots:
     void deal_display();
signals:
    void  display();
private:
    Ui::widget_child1 *ui;
    int semid;
     struct buffer *share_memry[Buffer_num];
     FILE *filein=nullptr;
         int file_end;
         char pa[100]="/lab3/get";
         char* pathname=nullptr;
        bool status;
        QString s;

};

#endif // WIDGET_CHILD1_H
