#ifndef MAINROLE_H
#define MAINROLE_H

class mainrole
{
public:
    mainrole();

    int atk;
    int defense;
    int HP;
    int MAX_HP;
    int golden;
    int Level;
    int EXP;
    int EXP_To_LevelUP;
    int floor;
    int X;
    int Y;

    bool Double_hit;//连击。
    double Crit_damage;//暴击伤害。
    double Crit;//暴击率。
    double Feed_on_Blood;//吸血比例。
    //属性删除！！！
    double HP_Rec;//血量恢复；

    void level_up();
};

#endif // MAINROLE_H
