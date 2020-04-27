#include "mainsence.h"
#include "ui_mainsence.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>

MainSence::MainSence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    ui->setupUi(this);
    //配置主场景


    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("CoinFlip");

    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮 的音效
    QSound *starSound= new QSound(":/res/TapButtonSound.wav",this);



    //开始按钮初始化
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡的场景
    chooseScene=new ChooseLeveScene;

    //监听选择关卡返回按钮信号
    connect(chooseScene,&ChooseLeveScene::chooseSceneBack,this,[=](){
        chooseScene->hide();        //先将选择关卡的页面隐藏
        this->show();//重新显示主场景
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug() << "clicked start";
        //播放开始音效
        starSound->play();
        //弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入到选择关卡场景中
        QTimer::singleShot(500,this,[=](){
            //进入到选择关卡的场景中
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();


        });

    });



}


void MainSence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainSence::~MainSence()
{
    delete ui;
}

