#include "mainrole.h"

mainrole::mainrole()
{
    atk=15;
    defense=10;
    HP=50;
    MAX_HP=50;
    golden=0;
    Level=1;
    EXP=0;

    Double_hit=0;
    Crit_damage=2;
    Crit=0;
    Feed_on_Blood=0;
    Damage_Redu=0;
    HP_Rec=0;
}

void mainrole::level_up()
{
    switch(this->Level)
        {case 1:if(this->EXP>=50){this->atk+=3;  this->defense+=5; this->MAX_HP+=15; this->HP=this->MAX_HP; this->Level=2; this->EXP-=50;}
                break;
         case 2:if(this->EXP>=100){this->atk+=7; this->defense+=8; this->MAX_HP+=25; this->HP=this->MAX_HP; this->Level=3; this->EXP-=100;}
                break;
         case 3:if(this->EXP>=220){this->atk+=10; this->defense+=11; this->MAX_HP+=40; this->HP=this->MAX_HP; this->Level=4; this->EXP-=220;}
                break;
         case 4:if(this->EXP>=400){this->atk+=15; this->defense+=13; this->MAX_HP+=70; this->HP=this->MAX_HP; this->Level=5; this->EXP-=300;}
                break;
         case 5:if(this->EXP>=550){this->atk+=20; this->defense+=17; this->MAX_HP+=100; this->HP=this->MAX_HP; this->Level=6; this->EXP-=420;}
                break;
         case 6:if(this->EXP>=720){this->atk+=30; this->defense+=25; this->MAX_HP+=150; this->HP=this->MAX_HP; this->Level=7; this->EXP-=720;}
                break;
         case 7:if(this->EXP>=1000){this->atk+=30; this->defense+=27; this->MAX_HP+=200; this->HP=this->MAX_HP; this->Level=8; this->EXP-=1000;}
                break;
        }
     return;
}
