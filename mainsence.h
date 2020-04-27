#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "chooselevescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainSence; }
QT_END_NAMESPACE

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    MainSence(QWidget *parent = nullptr);
    ~MainSence();

    //重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);

    ChooseLeveScene * chooseScene=NULL;

private:
    Ui::MainSence *ui;
};
#endif // MAINSENCE_H
