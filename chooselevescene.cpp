#include "chooselevescene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QSound>

ChooseLeveScene::ChooseLeveScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("ChooseScene");

    //创建菜单烂
    QMenuBar *bar= menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startmenue=bar->addMenu("Start");

    //创建退出 菜单项
    QAction *quitAction=startmenue->addAction("Exit");

    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡音效
    QSound *chooseSound= new QSound(":/res/TapButtonSound.wav",this);
    QSound *backSound= new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton *btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());

    //点击返回
    connect(btn,&MyPushButton::clicked,[=](){
        qDebug()<<"clicked";
        backSound->play();

        //告诉主场景 我返回了 主场景监听ChooseLevelScene 返回按钮
        //延时返回
        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();
        });


    });


    //选择关卡按钮
    for (int i=0;i<20;i++) {
     MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
     menuBtn->setParent(this);
     menuBtn->move(25+i%4 *70,130+i/4*70);

     //监听每个按钮的点击事件
     connect(menuBtn,&MyPushButton::clicked,[=](){

         //播放关卡音效
         chooseSound->play();

         QString str=QString("你选择的是第 %1 关").arg(i+1);
         qDebug()<<str;

     //进入到开始游戏场景里
         this->hide();              //隐藏上一页
         play=new PlayScene(i+1);
         play->show();

         //监听选择关卡返回按钮信号
         connect(play,&PlayScene::chooseSceneBack,this,[=](){
             this->show();      //先将选择关卡的页面隐藏
             delete play;
             play=NULL;
         });

     });


     QLabel * label = new QLabel;
     label->setParent(this);
     label->setFixedSize(menuBtn->width(),menuBtn->height());
     label->setText(QString::number(i+1));
     label->move(25+i%4*70,130+i/4*70);

     //设置label上的文字对其方式
     label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

     //设置让鼠标穿透
     label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void ChooseLeveScene::paintEvent(QPaintEvent *)
{
    //利用画家
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载第二个场景的标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);


}
