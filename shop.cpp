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
    c=1;
    n=11;
    this->setFixedSize(1000,550);
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
    arrow->setStyleSheet("color: rgb(255, 255, 255)");
    arrow->move(250,90);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(arrow_ShoworHide()));
    timer->start(500);

    for(int i=0;i<12;i++)
        for(int j=0;j<3;j++)
        {
            pus[i][j]=new QLabel(this);
            pus[i][j]->setText(mer[i][j]);
            if(i==1||i==2)
                pus[i][0]->setStyleSheet("color: rgb(0, 85, 255)");
            if(i==3||i==4||i==5||i==6)
                pus[i][0]->setStyleSheet("color: rgb(0, 170, 127)");
            if(i==7||i==8||i==9||i==10||i==11)
                pus[i][0]->setStyleSheet("color: rgb(255, 0, 0)");
        }
    hide();

}

void shop::hide()
{
    for(int i=0,c=0;i<12;i++,c++)
    {
        for(int j=0;j<3;j++)
        {
            if(pus[i][0]->isHidden())
            {
                c--;
                break;
            }
            if(j==0)
            {
                pus[i][j]->move(300,40*c+50);
            }
            if(j==1)
                pus[i][j]->move(400,40*c+50);
            if(j==2)
                pus[i][j]->move(850,40*c+50);
        }
    }
}

void shop::init()
{
    num=1;
    arrow->move(250,90);
    conversation->setText("你要挑选什么商品呢？");
    update();
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
    p.drawPixmap(-30,-15,1100,600,pix);
    pix.load(":/mota/pictures/merchant.png");
    p.drawPixmap(75,250,100,100,pix);
    pix.load(":/mota/pictures/shop_message.png");
    p.drawPixmap(20,100,220,200,pix);
    p.restore();

    hide();
}

void shop::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Down)
    {
        if(num<11)
        {
            num++;
            c++;
            while(pus[num][0]->isHidden())
            {
                num++;
                if(num>11)
                {
                    num=1;
                    c=1;
                    break;
                }
            }
        }
        else
        {
            num=1;
            c=1;
        }
        arrow->move(250,40*c+50);
        conversation->setText("你要挑选什么商品呢？");
        update();
        return;
    }
    if(event->key()==Qt::Key_Up)
    {
        if(num>1)
        {
            num--;
            c--;
            while(pus[num][0]->isHidden())
                num--;
        }
        else
        {
            num=11;
            while (pus[num][0]->isHidden())
            {
                num--;
            }
            c=n;
        }
        arrow->move(250,40*c+50);
        conversation->setText("你要挑选什么商品呢？");
        update();
        return;
    }
    if(event->key()==Qt::Key_Escape)
    {
        this->close();
    }
    if(event->key()==Qt::Key_Return)
    {
        buy();
        num=1;
        c=1;
    }
}

void shop::buy()
{
    if(Gold>=mer[num][2].toInt())
    {
        Gold-=mer[num][2].toInt();
        mygold->setText("你的金币为"+QString::number(Gold));
        conversation->setText("你已购买"+mer[num][0]+"。");
        if(num>6)
        {
            for(int j=0;j<3;j++)
                pus[num][j]->hide();
            n--;
        }
        arrow->move(250,90);
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
