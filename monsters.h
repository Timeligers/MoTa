#ifndef MONSTERS_H
#define MONSTERS_H
#include <QPixmap>

class monsters
{
public:
    monsters();

    int atk;
    int defense;
    int HP;
    int golden;
    int EXP;
    QPixmap pix;
    void mon(int i);
};

#endif // MONSTERS_H
