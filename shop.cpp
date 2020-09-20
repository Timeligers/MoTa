#include "shop.h"
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QTimer>

shop::shop(QWidget * parent)
    :QWidget(parent)
{
    num=1;
    this->setFixedSize(900,550);
    setWindowModality(Qt::ApplicationModal);//设置模态窗口。

    mygold = new QLabel(this);
    mygold->move(300,10);

    conversation = new QLabel(this);
    conversation->move(20,60);
    conversation->setFixedSize(220,200);
    conversation->setAlignment(Qt::AlignCenter);
    conversation->setText("你要挑选什么商品呢？");

    arrow = new QLabel(this);
    arrow->setText("->");
    arrow->move(250,90);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(arrow_ShoworHide()));
    timer->start(500);

    for(int i=0;i<12;i++)
        for(int j=0;j<3;j++)
        {
            pus[i][j]=new QLabel(this);
            pus[i][j]->setText(mer[i][j]);
            if(j==0)
                pus[i][j]->move(300,40*i+50);
            if(j==1)
                pus[i][j]->move(400,40*i+50);
            if(j==2)
                pus[i][j]->move(800,40*i+50);
        }
}

void shop::getgold(int gold)
{
    Gold=gold;
    mygold->setText("你的金币为"+QString::number(Gold));
}

void shop::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QPixmap pix;
    p.save();
    pix.load(":/mota/pictures/shop_background.png");
    p.drawPixmap(-30,-15,1000,600,pix);
    pix.load(":/mota/pictures/merchant.png");
    p.drawPixmap(75,250,100,100,pix);
    pix.load(":/mota/pictures/shop_message.png");
    p.drawPixmap(20,100,220,200,pix);
    p.restore();
}

void shop::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Down)
    {
        if(num<11)
        {
            num++;
            arrow->move(250,40*num+50);
            conversation->setText("你要挑选什么商品呢？");
            update();
        }
        return;
    }
    if(event->key()==Qt::Key_Up)
    {
        if(num>1)
        {
            num--;
            arrow->move(250,40*num+50);
            conversation->setText("你要挑选什么商品呢？");
            update();
        }
        return;
    }
    if(event->key()==Qt::Key_Escape)
    {
        num=1;
        arrow->move(250,90);
        conversation->setText("你要挑选什么商品呢？");
        update();
        this->hide();
    }
    if(event->key()==Qt::Key_Return)
    {
        buy();
    }
}

void shop::buy()
{
    if(Gold>=mer[num][2].toInt())
    {
        Gold-=mer[num][2].toInt();
        mygold->setText("你的金币为"+QString::number(Gold));
        conversation->setText("你已购买"+mer[num][0]+"。");
        update();
        emit saleit();
    }
    else
    {
        conversation->setText("你的金币不够购买这件商品。");
    }
    return;
}

void shop::arrow_ShoworHide()
{
    if(arrow->isHidden()==true)
    {
        arrow->show();
    }
    else
    {
        arrow->hide();
    }
}
