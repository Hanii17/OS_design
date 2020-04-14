#ifndef WIDGET_PARENT_H
#define WIDGET_PARENT_H

#include <QWidget>
#include<prama.h>
#include<QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget_parent; }
QT_END_NAMESPACE

class Widget_parent : public QWidget
{
    Q_OBJECT

public:
    Widget_parent(QWidget *parent = nullptr);
    ~Widget_parent();

private:
    Ui::Widget_parent *ui;
    int semid;
    struct buffer *share_memry[Buffer_num];
    int myshm_id[Buffer_num];


};
#endif // WIDGET_PARENT_H
