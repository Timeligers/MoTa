#include "monsters.h"

monsters::monsters()
{
}

void monsters::mon(int i)
{
    switch (i)
    {
        case 0:{this->atk=4;this->defense=2;this->HP=10;this->golden=10;this->EXP=8;}
               break;
        case 1:{this->atk=6;this->defense=5;this->HP=40;this->golden=25;this->EXP=26;}
               break;
        case 2:{this->atk=12;this->defense=10;this->HP=100;this->golden=35;this->EXP=50;}
               break;
        case 3:{this->atk=18;this->defense=15;this->HP=280;this->golden=60;this->EXP=75;}
               break;
        case 4:{this->atk=25;this->defense=20;this->HP=500;this->golden=95;this->EXP=110;}
               break;
        case 5:{this->atk=32;this->defense=22;this->HP=750;this->golden=120;this->EXP=150;}
               break;
    }
}
