#include "map.h"
#include "ui_map.h"
#include <QPixmap>
#include <QDebug>

static int floors[10][15][15]={{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,30,50,31,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,30,0,0,30,0,0,0,0,1},
                                {1,0,0,0,31,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,31,0,0,0,1},
                                {1,0,0,0,0,0,31,0,0,0,0,0,0,0,1},
                                {1,0,30,0,0,0,0,30,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,31,0,0,0,0,0,0,30,0,0,0,0,1},
                                {1,0,0,0,0,0,0,31,0,0,0,0,0,0,1},
                                {1,0,0,0,30,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,1,20,1,0,0,0,0,0,1},
                                {1,0,0,0,0,0,1,60,1,0,0,0,0,0,1},
                                {1,0,30,0,0,0,1,51,1,0,0,0,0,32,71},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第一层。0代表空位，1代表墙，2X代表门，3/4X代表怪物，4代表主角，5X代表钥匙，6X代表道具，70表示下楼，71表示上楼，72代表商店，80/1代表怪物。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {70,0,0,0,0,0,0,0,0,0,0,0,0,31,1},
                                {1,60,0,0,0,31,0,0,0,0,0,61,0,0,1},
                                {1,0,0,0,50,0,31,0,51,0,0,0,0,0,1},
                                {1,1,1,0,0,0,1,0,0,0,1,0,0,32,1},
                                {1,72,1,60,1,31,0,0,1,32,0,60,1,31,1},
                                {1,0,32,31,0,0,1,0,0,31,1,0,0,0,1},
                                {1,61,1,0,1,0,0,31,1,0,0,0,1,61,1},
                                {1,1,1,0,0,30,1,0,0,61,1,0,0,0,1},
                                {1,32,0,0,0,0,0,0,0,0,0,0,31,30,1},
                                {1,0,0,0,0,0,30,0,0,0,0,0,0,0,1},
                                {1,1,1,1,20,1,1,22,1,1,20,1,1,21,1},
                                {1,32,31,30,31,1,0,33,0,1,62,60,1,50,1},
                                {1,52,50,61,51,1,0,0,0,1,51,32,20,50,1},
                                {1,1,1,1,1,1,1,71,1,1,1,1,1,1,1}},//第二层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,60,31,32,0,1,0,0,0,0,0,22,34,71,1},
                                {1,31,0,0,32,20,0,50,0,0,0,1,1,1,1},
                                {1,0,32,31,61,1,0,0,0,0,0,0,0,0,1},
                                {1,31,1,1,1,1,1,1,21,1,1,1,1,1,1},
                                {1,0,1,52,50,50,50,1,32,1,33,0,60,61,1},
                                {1,0,1,52,51,51,51,20,0,21,32,0,60,61,1},
                                {1,32,1,1,1,1,1,1,0,1,1,1,1,1,1},
                                {1,0,1,33,32,32,0,0,33,0,0,0,32,0,1},
                                {1,60,1,1,1,1,1,1,0,1,1,1,1,1,1},
                                {1,0,1,61,33,32,31,20,0,21,62,0,1,70,1},
                                {1,0,1,60,33,32,31,1,32,1,63,0,1,0,1},
                                {1,31,1,1,1,1,1,1,1,1,1,1,1,0,1},
                                {1,0,0,61,0,0,0,31,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第三层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {70,0,0,60,0,32,0,0,31,0,0,32,0,0,1},
                                {1,1,1,1,1,1,21,1,1,1,1,1,1,0,1},
                                {1,0,0,61,0,0,0,0,0,0,0,0,1,0,1},
                                {1,30,1,1,1,1,1,1,1,1,1,0,34,0,1},
                                {1,61,1,0,0,0,21,0,0,0,1,32,1,0,1},
                                {1,0,1,0,1,22,1,1,1,0,1,0,1,30,1},
                                {1,31,1,32,1,0,35,71,1,0,1,21,1,0,1},
                                {1,0,1,0,1,0,1,1,1,0,1,33,1,0,1},
                                {1,32,34,0,1,30,0,0,61,0,1,32,1,0,1},
                                {1,0,1,0,1,1,1,1,34,1,1,33,1,0,1},
                                {1,32,1,0,0,0,0,0,0,0,50,0,1,0,1},
                                {1,0,1,1,20,1,1,1,1,1,1,1,1,0,1},
                                {1,33,0,0,0,0,0,0,0,0,0,20,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第四层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
                                {1,0,0,0,0,1,36,71,37,1,0,0,0,0,1},
                                {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
                                {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
                                {1,20,1,0,1,1,0,1,0,1,1,0,1,21,1},
                                {1,0,1,0,0,1,0,1,0,1,0,0,1,0,1},
                                {1,0,1,0,0,0,0,1,0,0,0,0,1,0,1},
                                {1,0,1,0,0,0,0,22,0,0,0,0,1,0,1},
                                {1,0,1,1,1,1,0,1,0,1,1,1,1,0,1},
                                {1,0,0,1,0,1,0,1,0,1,0,1,0,0,1},
                                {1,0,0,21,0,1,1,1,1,1,0,20,0,0,1},
                                {1,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
                                {1,0,0,1,1,1,70,0,0,1,1,1,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第五层。
                              };

Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    this->setFixedSize(1000,764);
    ui->setupUi(this);
    for(int i=0;i<3;i++)
    {
        keys[i]=0;
    }
    memcpy(map,floors[0],900);
    Superman.X=1;
    Superman.Y=1;
    Superman.floor=1;
    map[Superman.Y][Superman.X]=4;
    face_up=3;

    connect(&Shop,SIGNAL(saleit()),this,SLOT(getit()));
}

Map::~Map()
{
    delete ui;
}

void Map::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.save();
    printmap(p);
    p.restore();

    printdata();
}

void Map::printdata()
{
    ui->label_num_HP->setText(QString::number(Superman.HP)+"/"+QString::number(Superman.MAX_HP));
    ui->label_num_ATK->setText(QString::number(Superman.atk));
    ui->label_num_Def->setText(QString::number(Superman.defense));
    ui->label_num_EXP->setText(QString::number(Superman.EXP)+"/"+QString::number(Superman.EXP_To_LevelUP));//修改！！！
    ui->label_num_Level->setText(QString::number(Superman.Level));
    ui->label_num_golden->setText(QString::number(Superman.golden));
    ui->label_num_yellow_key->setText(QString::number(keys[0]));
    ui->label_num_blue_key->setText(QString::number(keys[1]));
    ui->label_num_red_key->setText(QString::number(keys[2]));
}

void Map::printmap(QPainter &p)
{
    QPixmap pix;
    pix.load(":/mota/pictures/background.bmp");
    p.drawPixmap(0,14,1000,750,pix);
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            switch (map[i][j])
            {
                case 1:pix.load(":/mota/pictures/wall.bmp");
                       p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                       break;
                case 4:mainrole_faceup(pix,p);
                       break;
                case 20:pix.load(":/mota/pictures/yellow_door.bmp");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 21:pix.load(":/mota/pictures/blue_door.bmp");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 22:pix.load(":/mota/pictures/red_door.bmp");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 30:pix.load(":/mota/pictures/monster_00.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 31:pix.load(":/mota/pictures/monster_01.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 32:pix.load(":/mota/pictures/monster_02.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 33:pix.load(":/mota/pictures/monster_03.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 34:pix.load(":/mota/pictures/monster_04.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 35:pix.load(":/mota/pictures/monster_05.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 36:pix.load(":/mota/pictures/monster_06.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 37:pix.load(":/mota/pictures/monster_07.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 38:pix.load(":/mota/pictures/monster_08.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 39:pix.load(":/mota/pictures/monster_09.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 40:pix.load(":/mota/pictures/monster_10.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 41:pix.load(":/mota/pictures/monster_11.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 42:pix.load(":/mota/pictures/monster_12.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 43:pix.load(":/mota/pictures/monster_13.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 44:pix.load(":/mota/pictures/monster_14.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 45:pix.load(":/mota/pictures/monster_15.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 46:pix.load(":/mota/pictures/monster_16.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 47:pix.load(":/mota/pictures/monster_17.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 48:pix.load(":/mota/pictures/monster_18.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 49:pix.load(":/mota/pictures/monster_19.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 50:pix.load(":/mota/pictures/yellow_key.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 51:pix.load(":/mota/pictures/blue_key.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 52:pix.load(":/mota/pictures/red_key.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 60:pix.load(":/mota/pictures/small_medcine.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 61:pix.load(":/mota/pictures/big_medcine.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 62:pix.load(":/mota/pictures/red_stone.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;//修改！！！！
                case 63:pix.load(":/mota/pictures/blue_stone.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;//修改！！！！
                case 70:pix.load(":/mota/pictures/downstairs.bmp");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 71:pix.load(":/mota/pictures/upstairs.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 72:pix.load(":/mota/pictures/merchant.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
//                case 80:
//                case 81:
            }
        }
}

void Map::mainrole_faceup(QPixmap pix, QPainter &p)
{
    int i=Superman.X,j=Superman.Y;
    switch (face_up)
    {
        case 1:pix.load(":/mota/pictures/up_00.png");
               break;
        case 2:pix.load(":/mota/pictures/right_01.png");
               break;
        case 3:pix.load(":/mota/pictures/down_00.png");
               break;
        case 4:pix.load(":/mota/pictures/left_01.png");
               break;
    }
    p.drawPixmap(250+50*i,14+50*j,50,50,pix);

}

void Map::keyReleaseEvent(QKeyEvent* event)
{
    this->grabKeyboard();
    if(event->key()==Qt::Key_Left)
    {
        move(Superman.X-1,Superman.Y);
        face_up=4;
    }
    else if(event->key()==Qt::Key_Right)
    {
        move(Superman.X+1,Superman.Y);
        face_up=2;
    }
    else if(event->key()==Qt::Key_Up)
    {
        move(Superman.X,Superman.Y-1);
        face_up=1;
    }
    else if(event->key()==Qt::Key_Down)
    {
        move(Superman.X,Superman.Y+1);
        face_up=3;
    }
    update();
}

void Map::move(int i, int j)
{
    if(map[j][i]==1||(i<0||i>14)||(j<0||j>14))
        return;
    if(map[j][i]/10==2)
    {
        if(keys[map[j][i]%10]!=0)
        {
            keys[map[j][i]%10]--;
        }
        else {return;}
    }
    if (map[j][i]/10==3||map[j][i]/10==4)
    {
        if(!fight(map[j][i]))
            return;
    }
    if(map[j][i]/10==5)
    {
        keys[map[j][i]%10]++;
    }
    if(map[j][i]/10==6)
    {
        if(map[j][i]==60) {Superman.HP+=10;}
        if(map[j][i]==61) {Superman.HP+=25;}
        if(map[j][i]==62) {Superman.atk+=3;}//修改！！！
        if(map[j][i]==63) {Superman.defense+=3;}//
        if(Superman.HP>Superman.MAX_HP)
            Superman.HP=Superman.MAX_HP;
    }
    if(map[j][i]==71)
    {
        upstair(Superman.floor);
        return;
    }
    if(map[j][i]==70)
    {
        downstair(Superman.floor);
        return;
    }
    if(map[j][i]==72)
    {
        shopping();
        return;
    }
    map[j][i]=4;
    Superman.X=i;
    Superman.Y=j;
    if(Superman.HP_Rec>0)
    {
        int rec=(Superman.MAX_HP-Superman.HP)*Superman.HP_Rec;//修改！！！
        if(Superman.HP<Superman.MAX_HP&&rec==0)
            Superman.HP++;
        else
            Superman.HP+=rec;
        if(Superman.HP>Superman.MAX_HP)
            Superman.HP=Superman.MAX_HP;
    }
    return;
}

void Map::upstair(int floor)
{
    memcpy(floors[floor-1],map,900);
    memcpy(map,floors[floor],900);
    floor+=1;
    switch (floor)
    {
    case 2:{Superman.X=1;
            Superman.Y=1;
            Superman.floor=2;
            break;
           }
    case 3:{Superman.X=13;
            Superman.Y=11;//修改！！！
            Superman.floor=3;
            break;
           }
    case 4:{Superman.X=1;
            Superman.Y=1;
            Superman.floor=4;
            break;
           }
    case 5:{Superman.X=7;
            Superman.Y=13;
            Superman.floor=5;
            break;
           }
    }
    map[Superman.Y][Superman.X]=4;
}

void Map::downstair(int floor)
{
    memcpy(floors[floor-1],map,900);
    memcpy(map,floors[floor-2],900);
    floor-=1;
    switch (floor)
    {
    case 1:{Superman.X=13;
            Superman.Y=13;
            Superman.floor=1;
            break;
           }
    case 2:{Superman.X=7;
            Superman.Y=13;
            Superman.floor=2;
            break;
            }
     case 3:{Superman.X=12;
             Superman.Y=1;//修改！！！
             Superman.floor=3;
             break;
            }
    case 4:{Superman.X=6;
            Superman.Y=7;
            Superman.floor=4;
            break;
           }
    }
    map[Superman.Y][Superman.X]=4;
}

bool Map::fight(int num)
{
    int n;
    if(num>=80)//编号20之后的怪物。
        n=num-60;
    else if(num<50)//编号20之前的怪物。
        n=num-30;
    Mon[n].mon(n);
    int m=Mon[n].HP,i=Superman.atk;//i:单次伤害;
    f1=1;
    a=0;
    b=0;
    c=0;
    srand((unsigned)time(nullptr));
     for(;m>0&&Superman.HP>0;)
        {if(rand()%100<Superman.Crit*100)
            {i=int(Superman.atk*Superman.Crit_damage);
             a++;
            }
         if(Superman.Double_hit)
            {m-=(i-Mon[n].defense);
             if(m<=0)
                break;
            }
         int k=(Mon[n].atk-Superman.defense);//修改！！！
         if(k>0)
            Superman.HP-=k;
         m-=i;
         c+=i;
         Superman.HP+=i*Superman.Feed_on_Blood;
         b+=i*Superman.Feed_on_Blood;
         if(Superman.HP>Superman.MAX_HP)
            Superman.HP=Superman.MAX_HP;
        }
     if(Superman.HP<=0)
        {
         //战败。
         return false;
        }
     else
        {Superman.golden+=Mon[n].golden;
         if(Superman.Level<20)//修改！！！
            Superman.EXP+=Mon[n].EXP;
         Superman.level_up();
         return true;
        }
}

void Map::shopping()
{
    Shop.init();
    Shop.getgold(Superman.golden);
    Shop.grabKeyboard();
    Shop.show();
    Shop.releaseKeyboard();
}

void Map::getit()//大量修改！！！！！！
{
    switch (Shop.num)
    {
        case 1:{Superman.HP+=10;
                if(Superman.HP>Superman.MAX_HP)
                    Superman.HP=Superman.MAX_HP;
               }break;
        case 2:{Superman.HP+=25;
                if(Superman.HP>Superman.MAX_HP)
                    Superman.HP=Superman.MAX_HP;
               }break;
        case 3:Superman.defense+=8;
               break;//修改！！！
        case 4:{Superman.atk+=3;
                Superman.Crit+=0.1;
               }break;//
        case 5:{Superman.atk+=4;
                Superman.Feed_on_Blood+=0.05;
               }break;//
        case 6:Superman.atk+=8;
               break;//
        case 7:{Superman.atk+=22;
                Superman.Crit+=0.5;
                Superman.Crit_damage+=0.25;
               }break;//
        case 8:{Superman.Double_hit=1;
                Superman.atk+=18;
                Superman.Crit+=0.3;
                Superman.Crit_damage+=0.2;
               }break;//
        case 9:{Superman.atk+=20;
                Superman.Feed_on_Blood+=0.32;
               }break;//
        case 10:{Superman.MAX_HP+=250;
                 Superman.HP+=250;
                 Superman.defense+=20;
                }break;//修改！！！
        case 11:{Superman.MAX_HP+=400;
                 Superman.HP+=400;
                 Superman.defense+=18;//修改！！！
                 Superman.HP_Rec+=0.02;
                }break;//
    }
    Superman.golden-=Shop.mer[Shop.num][2].toInt();
    update();
}
