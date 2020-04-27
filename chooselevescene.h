#ifndef CHOOSELEVESCENE_H
#define CHOOSELEVESCENE_H
#include"playscene.h"

#include <QMainWindow>

class ChooseLeveScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLeveScene(QWidget *parent = nullptr);


    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    //游戏场景的对想指针
    PlayScene *play =NULL;

signals:
    //写一个自定义的信号 告诉主场景 点击返回
    void chooseSceneBack();
};

#endif // CHOOSELEVESCENE_H
