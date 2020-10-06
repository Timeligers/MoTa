#include "monsterlist_item.h"
#include <QWidget>

MonsterList_item::MonsterList_item(QWidget *parent): QWidget(parent)
{

}

//初始化item
void MonsterList_item::initItem()
{

        head = new QLabel(this);
        label_hp = new QLabel(this);
        label_atk = new QLabel(this);
        label_pdef = new QLabel(this);
        label_exp = new QLabel(this);
        label_gold = new QLabel(this);
        label_damage = new QLabel(this);

        label_hp_val = new QLabel(this);
        label_atk_val = new QLabel(this);
        label_pdef_val = new QLabel(this);
        label_exp_val = new QLabel(this);
        label_gold_val = new QLabel(this);
        label_damage_val = new QLabel(this);

        //设置颜色，对齐方式
        label_hp->setStyleSheet("color: rgb(160, 160, 160);font: 15pt;");
        label_hp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_hp->setFixedSize(100, 30);
        label_hp->setText("生命");

        label_atk->setStyleSheet("color: rgb(160, 160, 160);font: 15pt;");
        label_atk->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_atk->setFixedSize(100, 30);
        label_atk->setText("攻击");

        label_pdef->setStyleSheet("color: rgb(160, 160, 160);font: 15pt;");
        label_pdef->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_pdef->setFixedSize(100, 30);
        label_pdef->setText("防御");

        label_exp->setStyleSheet("color: rgb(160, 160, 160);font: 15pt;");
        label_exp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_exp->setFixedSize(100, 30);
        label_exp->setText("经验");

        label_gold->setStyleSheet("color: rgb(160, 160, 160);font: 15pt;");
        label_gold->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_gold->setFixedSize(100, 30);
        label_gold->setText("金币");

        label_damage->setStyleSheet("color: rgb(160, 160, 160);font: 15pt;");
        label_damage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_damage->setFixedSize(200, 30);
        label_damage->setText("预计最高伤害");



        label_hp_val->setStyleSheet("color:white;font: 15pt;");
        label_hp_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_hp_val->setFixedSize(150, 30);

        label_atk_val->setStyleSheet("color:white;font: 15pt;");
        label_atk_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_atk_val->setFixedSize(150, 30);

        label_pdef_val->setStyleSheet("color:white;font: 15pt;");
        label_pdef_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_pdef_val->setFixedSize(150, 30);

        label_exp_val->setStyleSheet("color:white;font: 15pt;");
        label_exp_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_exp_val->setFixedSize(150, 30);

        label_gold_val->setStyleSheet("color:white;font: 15pt;");
        label_gold_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_gold_val->setFixedSize(150, 30);

        label_damage_val->setStyleSheet("color:white;font: 15pt;");
        label_damage_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label_damage_val->setFixedSize(300, 30);

        //设置头像大小
        head->setFixedSize(60,60);

        //布局
        head->move(40, 30);


        label_hp->move(120, 30);
        label_atk->move(270, 30);
        label_pdef->move(410, 30);
        label_hp_val->move(150, 30);
        label_atk_val->move(300, 30);
        label_pdef_val->move(440, 30);

        label_exp->move(120, 70);
        label_gold->move(270, 70);
        label_damage->move(420, 70);
        label_exp_val->move(150, 70);
        label_gold_val->move(300, 70);
        label_damage_val->move(490, 70);
}
