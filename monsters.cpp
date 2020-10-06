#include "monsters.h"

monsters::monsters()
{
}

void monsters::mon(int i)
{
    switch (i)
    {
    case 0:{this->atk=10;this->defense=0;this->HP=15;this->golden=5;this->EXP=8;this->pix.load(":/mota/pictures/monster_00.png");}
           break;
    case 1:{this->atk=13;this->defense=4;this->HP=35;this->golden=12;this->EXP=20;this->pix.load(":/mota/pictures/monster_01.png");}
           break;
    case 2:{this->atk=18;this->defense=10;this->HP=70;this->golden=35;this->EXP=45;this->pix.load(":/mota/pictures/monster_02.png");}
           break;
    case 3:{this->atk=28;this->defense=14;this->HP=165;this->golden=55;this->EXP=65;this->pix.load(":/mota/pictures/monster_03.png");}
           break;
    case 4:{this->atk=35;this->defense=22;this->HP=380;this->golden=72;this->EXP=115;this->pix.load(":/mota/pictures/monster_04.png");}
           break;
    case 5:{this->atk=45;this->defense=30;this->HP=600;this->golden=85;this->EXP=135;this->pix.load(":/mota/pictures/monster_05.png");}
           break;
    case 6:{this->atk=50;this->defense=45;this->HP=850;this->golden=107;this->EXP=170;this->pix.load(":/mota/pictures/monster_06.png");}
           break;
    case 7:{this->atk=56;this->defense=30;this->HP=600;this->golden=118;this->EXP=195;this->pix.load(":/mota/pictures/monster_07.png");}
           break;
    case 8:{this->atk=60;this->defense=45;this->HP=500;this->golden=400;this->EXP=550;this->pix.load(":/mota/pictures/monster_08.png");}
           break;//福利怪。
    case 9:{this->atk=72;this->defense=58;this->HP=920;this->golden=125;this->EXP=228;this->pix.load(":/mota/pictures/monster_09.png");}
           break;
    case 10:{this->atk=84;this->defense=65;this->HP=975;this->golden=133;this->EXP=242;this->pix.load(":/mota/pictures/monster_10.png");}
           break;
    case 11:{this->atk=92;this->defense=83;this->HP=1120;this->golden=146;this->EXP=256;this->pix.load(":/mota/pictures/monster_11.png");}
            break;
    case 12:{this->atk=115;this->defense=100;this->HP=1350;this->golden=152;this->EXP=268;this->pix.load(":/mota/pictures/monster_12.png");}
            break;
    case 13:{this->atk=120;this->defense=110;this->HP=1800;this->golden=177;this->EXP=295;this->pix.load(":/mota/pictures/monster_13.png");}
            break;
    case 14:{this->atk=145;this->defense=140;this->HP=2050;this->golden=200;this->EXP=315;this->pix.load(":/mota/pictures/monster_14.png");}
            break;
    case 15:{this->atk=152;this->defense=155;this->HP=2230;this->golden=213;this->EXP=338;this->pix.load(":/mota/pictures/monster_15.png");}
            break;
    case 16:{this->atk=172;this->defense=158;this->HP=2500;this->golden=229;this->EXP=355;this->pix.load(":/mota/pictures/monster_16.png");}
            break;
    case 17:{this->atk=184;this->defense=162;this->HP=2720;this->golden=244;this->EXP=369;this->pix.load(":/mota/pictures/monster_17.png");}
            break;
    case 18:{this->atk=192;this->defense=172;this->HP=2950;this->golden=266;this->EXP=384;this->pix.load(":/mota/pictures/monster_18.png");}
            break;
    case 19:{this->atk=198;this->defense=188;this->HP=3100;this->golden=275;this->EXP=400;this->pix.load(":/mota/pictures/monster_19.png");}
            break;
    case 20:{this->atk=220;this->defense=235;this->HP=3700;this->golden=1350;this->EXP=8000;this->pix.load(":/mota/pictures/monster_20.png");}
            break;
    case 21:{this->atk=350;this->defense=300;this->HP=5000;this->golden=10000;this->EXP=99999;this->pix.load(":/mota/pictures/boss.png");}
            break;
    }
}
