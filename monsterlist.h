#ifndef MONSTERLIST_H
#define MONSTERLIST_H

#include <QLabel>
#include <QListWidget>
#include "map.h"

class MonsterList: public QListWidget
{
    Q_OBJECT

public:
    explicit MonsterList(QListWidget *person = nullptr);



    void addItem(int& monsterNum, mainrole& Superman, monsters Mon[]); //在列表中新加一项
    int cal_damage(int monsterNum,mainrole Superman, monsters Mon[]);

private:
    int item_index;

};

#endif // MONSTERLIST_H
