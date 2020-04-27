#include "mycoin.h"
#include<QDebug>
#include<QPushButton>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}


MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
        qDebug()<<"error";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


    //初始化定时器对象
    timer1 =new QTimer(this);
    timer2 = new QTimer(this);


    //监听正面翻反面的信号，并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str3=QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str3);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;
            timer1->stop();
        }

    });

    //监听反面翻正面的信号，并且反转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str4=QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str4);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;
            timer2->stop();
        }

    });


}


void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation==true||this->isWin==true)
    {
        return;
    }else
    {
        QPushButton::mousePressEvent(e);
    }
}


//改变正反面的方法
void MyCoin::changeFlag()
{
    //如果是正面  翻成反面
    if(this->flag)
    {
        //开始正面翻反面的定时器
        timer1->start(30);      //30毫秒发送一次timeout 信号
        isAnimation=true;
        this->flag=false;
    }else{
        //开始反面翻正面的定时器
        timer2->start(30);      //30毫秒发送一次timeout 信号
        isAnimation=true;
        this->flag=true;
    }
}

