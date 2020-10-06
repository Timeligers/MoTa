#include "monsterlist.h"
#include "monsterlist_item.h"
#include <QPalette>
#include <QWidget>
#include "map.h"
#include <QPixmap>
#include <QDebug>

//这里我们把monsterlist类和monsterlist_item类连起来看
//由于我们要实现一个动态的，根据游戏进程变化的怪物列表，就不适合使用UI设计的方面
//所以item类主要实现怪物列表中每一个怪物Item的初始化
//由于要重复构造item，所以要单独写一个item类
//而list类可以通过成员函数additem逐个增加怪物列表中的怪物数据
//其实这两个类的关系就相当于Qlistwidget和Qlistwidgetitem的关系

MonsterList::MonsterList(QListWidget *parent): QListWidget(parent)//从qlistwidget继承的类的构造函数
{
    setFocusPolicy(Qt::NoFocus);//去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭
    //设置stylesheet,斜杠可以做到代码分行，用双引号也可以
    this->setStyleSheet("QListWidget{\
                        background:black;\
                        color:white;\
                        border:none;\
                    }\
                    QListWidget::item{\
                        border:none;\
                            height: 110px;\
                    }\
                    QScrollBar:vertical {\
                        background:transparent;\
                        width:9px;\
                        margin: 0px 0px 2px 0px;\
                    }\
                    QScrollBar::handle:vertical {\
                        background: rgb(195, 195, 195);\
                        min-height: 20px;\
                        border-radius: 3px;\
                    }\
                    QScrollBar::handle:vertical:hover{\
                        background:rgba(0,0,0,30%);\
                    }\
                    QScrollBar::add-line:vertical {\
                        height: 0px;\
                        subcontrol-position: bottom;\
                        subcontrol-origin: margin;\
                    }\
                    QScrollBar::sub-line:vertical {\
                        height: 0px;\
                        subcontrol-position: top;\
                        subcontrol-origin: margin;\
                    }");
    item_index = 0;
}






void MonsterList::addItem(int &monsterNum, mainrole &Superman, monsters Mon[]){

    MonsterList_item* temp = new MonsterList_item(); //创建一个自定义的listitem类

    temp->initItem();

    temp->label_hp_val->setText(QString::number(Mon[monsterNum].HP));
    temp->label_atk_val->setText(QString::number(Mon[monsterNum].atk));
    temp->label_pdef_val->setText(QString::number(Mon[monsterNum].defense));
    temp->label_exp_val->setText(QString::number(Mon[monsterNum].EXP));
    temp->label_gold_val->setText(QString::number(Mon[monsterNum].golden));
    int exp_damage = cal_damage(monsterNum, Superman, Mon);
    if (exp_damage >= 0)
        temp->label_damage_val->setText(QString::number(exp_damage));
    else {
        temp->label_damage_val->setText("?????");
    }


    Mon[monsterNum].pix.scaled(temp->head->size(), Qt::KeepAspectRatio);
    temp->head->setScaledContents(true);
    temp->head->setPixmap(Mon[monsterNum].pix);
    temp->head->show();
//增加list中的item
    QListWidgetItem* newItem = new QListWidgetItem();
    this->insertItem(0, newItem);
    this->setItemWidget(newItem, temp);
    newItem->setHidden(false);
;}

//计算伤害
int MonsterList::cal_damage(int monsterNum,mainrole Superman, monsters Mon[])
{

    if (Superman.atk<=Mon[monsterNum].defense)
    {
        if (Mon[monsterNum].atk > Superman.defense)
            return -1;
        else
            return -2;
    }
    else{
    if (Mon[monsterNum].atk > Superman.defense)
    {
        int atk_times = (Mon[monsterNum].HP - 1) / (Superman.atk - Mon[monsterNum].defense)+1;
        return atk_times *(Mon[monsterNum].atk - Superman.defense);
    }
    else{
        return 0;
    }
    }
}
