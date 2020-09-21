#include "mainrole.h"

mainrole::mainrole()
{
    atk=12;
    defense=5;
    HP=100;
    MAX_HP=100;//属性修改！！
    golden=0;
    Level=1;
    EXP=0;
    EXP_To_LevelUP=50;//属性添加！！！

    Double_hit=0;
    Crit_damage=2;
    Crit=0;
    Feed_on_Blood=0;
    //属性删除！！！
    HP_Rec=0;
}

void mainrole::level_up()//全部数据修改！！！
{
    switch(this->Level)
        {case 1:if(this->EXP>=50){this->atk+=3;  this->defense+=2; this->MAX_HP+=30; this->HP=this->MAX_HP; this->Level=2; this->EXP-=50; this->EXP_To_LevelUP=100;}
                break;
         case 2:if(this->EXP>=100){this->atk+=3; this->defense+=2; this->MAX_HP+=35; this->HP=this->MAX_HP; this->Level=3; this->EXP-=100; this->EXP_To_LevelUP=220;}
                break;
         case 3:if(this->EXP>=220){this->atk+=4; this->defense+=3; this->MAX_HP+=45; this->HP=this->MAX_HP; this->Level=4; this->EXP-=220; this->EXP_To_LevelUP=400;}
                break;
         case 4:if(this->EXP>=400){this->atk+=5; this->defense+=4; this->MAX_HP+=60; this->HP=this->MAX_HP; this->Level=5; this->EXP-=400; this->EXP_To_LevelUP=550;}
                break;
         case 5:if(this->EXP>=550){this->atk+=7; this->defense+=5; this->MAX_HP+=70; this->HP=this->MAX_HP; this->Level=6; this->EXP-=550; this->EXP_To_LevelUP=680;}
                break;
         case 6:if(this->EXP>=680){this->atk+=8; this->defense+=5; this->MAX_HP+=80; this->HP=this->MAX_HP; this->Level=7; this->EXP-=680; this->EXP_To_LevelUP=900;}
                break;
         case 7:if(this->EXP>=900){this->atk+=10; this->defense+=6; this->MAX_HP+=100; this->HP=this->MAX_HP; this->Level=8; this->EXP-=900; this->EXP_To_LevelUP=1240;}
                break;
         case 8:if(this->EXP>=1240){this->atk+=12; this->defense+=7; this->MAX_HP+=130; this->HP=this->MAX_HP; this->Level=9; this->EXP-=1240; this->EXP_To_LevelUP=1500;}
                break;
         case 9:if(this->EXP>=1500){this->atk+=15; this->defense+=10; this->MAX_HP+=155; this->HP=this->MAX_HP; this->Level=10; this->EXP-=1500; this->EXP_To_LevelUP=1720;}
                break;
         case 10:if(this->EXP>=1720){this->atk+=16; this->defense+=12; this->MAX_HP+=180; this->HP=this->MAX_HP; this->Level=11; this->EXP-=1720; this->EXP_To_LevelUP=1980;}
                break;
         case 11:if(this->EXP>=1980){this->atk+=17; this->defense+=22; this->MAX_HP+=220; this->HP=this->MAX_HP; this->Level=12; this->EXP-=1980; this->EXP_To_LevelUP=2080;}
                break;
         case 12:if(this->EXP>=2080){this->atk+=13; this->defense+=7; this->MAX_HP+=230; this->HP=this->MAX_HP; this->Level=13; this->EXP-=2080; this->EXP_To_LevelUP=2200;}
                break;
         case 13:if(this->EXP>=2200){this->atk+=16; this->defense+=10; this->MAX_HP+=250; this->HP=this->MAX_HP; this->Level=14; this->EXP-=2200; this->EXP_To_LevelUP=2350;}
                break;
         case 14:if(this->EXP>=2350){this->atk+=17; this->defense+=16; this->MAX_HP+=265; this->HP=this->MAX_HP; this->Level=15; this->EXP-=2350; this->EXP_To_LevelUP=2850;}
                break;
         case 15:if(this->EXP>=2850){this->atk+=20; this->defense+=20; this->MAX_HP+=290; this->HP=this->MAX_HP; this->Level=16; this->EXP-=2850; this->EXP_To_LevelUP=3000;}
                break;
         case 16:if(this->EXP>=3000){this->atk+=25; this->defense+=24; this->MAX_HP+=345; this->HP=this->MAX_HP; this->Level=17; this->EXP-=3000; this->EXP_To_LevelUP=3150;}
                break;
         case 17:if(this->EXP>=3150){this->atk+=22; this->defense+=21; this->MAX_HP+=350; this->HP=this->MAX_HP; this->Level=18; this->EXP-=3150; this->EXP_To_LevelUP=3500;}
                break;
         case 18:if(this->EXP>=3500){this->atk+=22; this->defense+=16; this->MAX_HP+=355; this->HP=this->MAX_HP; this->Level=19; this->EXP-=3500; this->EXP_To_LevelUP=4800;}
                break;
         case 19:if(this->EXP>=4800){this->atk+=33; this->defense+=25; this->MAX_HP+=500; this->HP=this->MAX_HP; this->Level=20; this->EXP_To_LevelUP=9999; this->EXP=this->EXP_To_LevelUP;}
                break;
        }
     return;
}
