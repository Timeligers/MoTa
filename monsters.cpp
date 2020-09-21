#include "monsters.h"

monsters::monsters()
{
}

void monsters::mon(int i)
{
    switch (i)
    {
        case 0:{this->atk=10;this->defense=0;this->HP=15;this->golden=5;this->EXP=8;}
               break;
        case 1:{this->atk=13;this->defense=4;this->HP=35;this->golden=28;this->EXP=26;}
               break;
        case 2:{this->atk=18;this->defense=10;this->HP=85;this->golden=40;this->EXP=52;}
               break;
        case 3:{this->atk=24;this->defense=12;this->HP=240;this->golden=70;this->EXP=95;}
               break;
        case 4:{this->atk=32;this->defense=18;this->HP=400;this->golden=85;this->EXP=130;}
               break;
        case 5:{this->atk=40;this->defense=25;this->HP=520;this->golden=100;this->EXP=150;}
               break;
        case 6:{this->atk=48;this->defense=32;this->HP=900;this->golden=140;this->EXP=170;}
               break;
        case 7:{this->atk=53;this->defense=25;this->HP=680;this->golden=130;this->EXP=180;}
               break;
        case 8:{this->atk=55;this->defense=30;this->HP=500;this->golden=300;this->EXP=500;}
               break;//福利怪。
        case 9:{this->atk=63;this->defense=36;this->HP=875;this->golden=145;this->EXP=240;}
               break;
        case 10:{this->atk=68;this->defense=42;this->HP=920;this->golden=160;this->EXP=310;}
               break;
        case 11:{this->atk=72;this->defense=65;this->HP=1080;this->golden=175;this->EXP=385;}
                break;
        case 12:{this->atk=105;this->defense=90;this->HP=1350;this->golden=200;this->EXP=420;}
                break;
        case 13:{this->atk=120;this->defense=100;this->HP=1800;this->golden=225;this->EXP=470;}
                break;
        case 14:{this->atk=124;this->defense=108;this->HP=2050;this->golden=275;this->EXP=520;}
                break;
        case 15:{this->atk=138;this->defense=121;this->HP=2230;this->golden=320;this->EXP=560;}
                break;
        case 16:{this->atk=148;this->defense=155;this->HP=2500;this->golden=370;this->EXP=600;}
                break;
        case 17:{this->atk=152;this->defense=162;this->HP=2720;this->golden=400;this->EXP=620;}
                break;
        case 18:{this->atk=168;this->defense=172;this->HP=2950;this->golden=575;this->EXP=650;}
                break;
        case 19:{this->atk=170;this->defense=188;this->HP=3100;this->golden=620;this->EXP=700;}
                break;
        case 20:{this->atk=220;this->defense=200;this->HP=3700;this->golden=2000;this->EXP=7300;}
                break;
        case 21:{this->atk=350;this->defense=300;this->HP=5000;this->golden=10000;this->EXP=99999;}
                break;
    }
}
