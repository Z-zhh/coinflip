#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QAction>
#include<QDebug>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QSound>

#include<QPropertyAnimation>


//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str=QString("entered num of level %1").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("game Scene");

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu=bar->addMenu("Start");

    //创建菜单项
    QAction *quitAction=startMenu->addAction("quit");

    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //音效加入
    QSound *backSound= new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipSound= new QSound(":/res/ConFlipSound.wav",this);
    QSound *winSound= new QSound(":/res/LevelWinSound.wav",this);



    //返回按钮
    MyPushButton *btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());

    //点击返回
    connect(btn,&MyPushButton::clicked,[=](){
        qDebug()<<"gameScene clicked";
            backSound->play();

        //告诉主场景 我返回了 主场景监听ChooseLevelScene 返回按钮
        //延时返回
        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();
        });


    });

    //显示当前的关卡数
    QLabel *label=new QLabel;
    label->setParent(this);

    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(15);
    QString str1 =QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);

    label->setText(str1);

    label->setGeometry(30,this->height()-50,120,50);


    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j =0 ;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }


    //胜利图片的显示
    QLabel *winLabel= new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());





    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j =0;j<4;j++)
        {
        //绘制背景图片
        QPixmap pix=(QPixmap(":/res/BoardNode.png"));
        QLabel *label1= new QLabel;

        label1->setGeometry(0,0,pix.width(),pix.height());
        label->setPixmap(pix);
        label1->setParent(this);
        label1->move(57+i*50,200+j*50);

        //创建金币
        QString str2;
        if(gameArray[i][j]==1)
        {
            //显示金币
            str2=":/res/Coin0001.png";
        }else
        {
            //显示银币
            str2=":/res/Coin0008.png";
        }
        MyCoin * coin =new MyCoin(str2);
        coin->setParent(this);
        coin->move(59+i*50,204+j*50);


        //给金币属性赋值
        coin->posX=i;
        coin->posY=j;
        coin->flag =this->gameArray[i][j];          //1 zheng 0 fan


        //将金币加入二维数组，以便后期维护
        coinBtn[i][j]=coin;


        //点击金币 进行反转
        connect(coin,&MyCoin::clicked,[=](){
            flipSound->play();


            coin->changeFlag();
            this->gameArray[i][j]=(this->gameArray[i][j] ==0 ? 1 : 0);


            //翻转周围金币
            //延时翻转
            QTimer::singleShot(300,this,[=](){

                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->coinBtn[i][j]->isWin=true;
                    }
                }





                if(coin->posX+1<=3) //周围右侧金币反转条件
                {
                    coinBtn[coin->posX+1][coin->posY]->changeFlag();
                    this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;

                }
                //周围左侧硬币反转条件
                if(coin->posX-1>=0)
                {
                    coinBtn[coin->posX-1][coin->posY]->changeFlag();
                    this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;

                }
                //上侧金币反转
                if(coin->posY-1>=0)
                {
                    coinBtn[coin->posX][coin->posY-1]->changeFlag();
                    this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;

                }
                //下侧金币反转
                if(coin->posY+1<=3)
                {
                    coinBtn[coin->posX][coin->posY+1]->changeFlag();

                    this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;

                }

                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->coinBtn[i][j]->isWin=false;
                    }
                }


                //判断是否胜利
                this->isWin=true;
                for(int i=0;i<4;i++)
                {
                    for(int j =0;j<4;j++)
                    {
                        if(coinBtn[i][j]->flag==false)      //只要有一个是反面 ，算失败
                            this->isWin=false;
                        break;
                    }
                }
                if(this->isWin==true)
                {

                    winSound->play();
                    //胜利了
                    qDebug()<<" game win";
                    //将所有标志都改为true
                    for(int i=0;i<4;i++)
                    {
                        for(int j =0 ;j<4;j++)
                        {
                           coinBtn[i][j]->isWin=true;
                        }
                    }

                    //胜利板块砸下来

                    QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry"); //谁使用动画，谁放进去

                    //设置时间间隔
                    animation->setDuration(1000);
                    //设置开始位置
                    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));

                    //设置结束位置
                    animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                    //设置缓和曲线
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    //执行动画
                    animation->start();
                }
            });

        });




        }
    }


}


void PlayScene::paintEvent(QPaintEvent *)
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


