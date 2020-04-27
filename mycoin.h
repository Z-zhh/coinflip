#ifndef MYCOIN_H
#define MYCOIN_H

#include<QTimer>


#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //参数代表 传入的金币路径还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    //正反标识
    bool flag;



    //改变标志的方法
    void changeFlag();

    QTimer *timer1;
    QTimer *timer2;
    int min= 1;
    int max= 8;

    //执行动画的标志
    bool isAnimation=false;


    //重写按下
    void mousePressEvent(QMouseEvent *a);


    //是否胜利
       bool isWin=false;




signals:

};

#endif // MYCOIN_H
