#ifndef PALYSCENE_H
#define PALYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex;         //内部成员属性，记录所选关卡

    //重写paintEvent
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];        //二维数组 维护每个关卡具体的数据


    MyCoin * coinBtn[4][4];

    //胜利标识
    bool isWin=false;


signals:
    void chooseSceneBack();
};

#endif // PALYSCENE_H
