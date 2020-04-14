#ifndef WIDGET_CHILD2_H
#define WIDGET_CHILD2_H

#include <QWidget>
#include<prama.h>
#include<QString>
#include<QByteArray>
#include<QMessageBox>

namespace Ui {
class widget_child2;
}

class widget_child2 : public QWidget
{
    Q_OBJECT

public:
    explicit widget_child2(QWidget *parent = nullptr);
    ~widget_child2();
    void start_write();

private slots:
    void on_pushButton_clicked();

private:
    Ui::widget_child2 *ui;
    int semid;
     struct buffer *share_memry[Buffer_num];
     FILE *fileout=NULL;
        char* pathname1=nullptr;
        bool status;
        char pa2[100]="/lab3/out";
};

#endif // WIDGET_CHILD2_H
