#ifndef MONSTERLIST_ITEM_H
#define MONSTERLIST_ITEM_H


#include <QWidget>
#include <QPixmap>
#include <QLabel>

class MonsterList_item: public QWidget
{
    Q_OBJECT
public:
    explicit MonsterList_item(QWidget* parent=nullptr);
    QLabel* head;
    QLabel* label_hp;
    QLabel* label_atk;
    QLabel* label_pdef;
    QLabel* label_exp;
    QLabel* label_gold;
    QLabel* label_damage;

    QLabel* label_hp_val;
    QLabel* label_atk_val;
    QLabel* label_pdef_val;
    QLabel* label_exp_val;
    QLabel* label_gold_val;
    QLabel* label_damage_val;
    void initItem();
};

#endif // MONSTERLIST_ITEM_H
