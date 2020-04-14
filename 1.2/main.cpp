#include "widget_parent.h"
#include"widget_child1.h"
#include"widget_child2.h"
#include <QApplication>
#include<sys/types.h>
#include<sys/sem.h>
#include<wait.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdio.h>
#include<QObject>
#include<signal.h>

int main(int argc, char *argv[])
{

    int pid1;
    if((pid1  = fork()) == 0){
        int pid2;
        if((pid2= fork())==0)
        {
            QApplication a2(argc, argv);
            widget_child2 w2;
            w2.show();
            a2.exec();
            exit(0);}

         QApplication a1(argc, argv);
         widget_child1 w1;
         w1.show();
         a1.exec();
         exit(0);
     }
    QApplication a(argc, argv);
    Widget_parent w;
    w.show();
    a.exec();

    return 0;
}
