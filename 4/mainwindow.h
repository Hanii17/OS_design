#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include<QString>
#include<QTextStream>
#include<QDir>
#include<unistd.h>
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void showSysInfo();
   void showprocess();
   void updateMem();
   void updateCpu();
public slots:
   void Update();
private slots:
   void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool if_monitor;
};
#endif // MAINWINDOW_H
