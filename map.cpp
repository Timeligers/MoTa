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
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第一层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {70,0,0,0,0,0,0,0,0,0,0,0,0,31,1},
                                {1,60,0,0,0,31,0,0,0,0,0,61,0,0,1},
                                {1,0,0,0,50,0,31,0,51,0,0,0,0,0,1},
                                {1,31,0,0,1,0,0,0,1,0,0,0,1,32,1},
                                {1,80,1,0,60,31,1,0,0,32,1,60,31,0,1},
                                {1,0,0,31,1,0,0,0,1,0,31,0,1,0,1},
                                {1,0,1,0,0,0,1,31,0,0,1,0,0,61,1},
                                {1,0,0,0,1,30,0,0,1,61,0,0,1,0,1},
                                {1,32,0,0,0,0,0,0,0,0,0,0,31,30,1},
                                {1,0,0,0,0,0,30,0,0,0,0,0,0,0,1},
                                {1,1,1,1,20,1,1,22,1,1,20,1,1,21,1},
                                {1,32,0,0,31,1,0,33,0,1,63,0,1,50,1},
                                {1,52,50,61,51,1,0,0,0,1,51,32,20,50,1},
                                {1,1,1,1,1,1,1,71,1,1,1,1,1,1,1}},//第二层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,1,0,0,0,0,0,0,0,71,1},
                                {1,31,0,0,0,20,0,50,0,0,0,0,0,0,1},
                                {1,1,21,1,0,1,0,0,0,0,0,0,0,0,1},
                                {1,0,0,1,1,1,1,1,1,1,1,21,1,1,1},
                                {1,0,32,1,63,33,0,1,31,60,30,0,32,0,1},
                                {1,0,0,1,0,61,31,1,30,32,33,32,0,0,1},
                                {1,0,30,1,0,0,0,1,60,31,62,0,31,0,1},
                                {1,0,0,1,60,33,32,20,32,51,32,31,0,0,1},
                                {1,0,0,1,32,31,0,1,61,33,30,60,0,0,1},
                                {1,0,0,1,31,60,0,1,60,0,0,32,0,0,1},
                                {1,0,60,1,63,0,31,1,31,50,31,0,1,1,1},
                                {1,0,0,1,1,1,1,1,1,1,1,1,1,70,1},
                                {1,34,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第三层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {70,0,0,60,0,32,0,0,31,0,0,32,0,0,1},
                                {1,1,1,1,1,1,21,1,1,1,1,1,1,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
                                {1,0,1,1,1,1,1,1,1,1,1,0,34,0,1},
                                {1,0,1,0,0,0,21,0,0,0,1,0,1,0,1},
                                {1,0,1,0,1,0,35,71,1,0,1,0,1,0,1},
                                {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
                                {1,0,1,0,1,0,0,0,0,0,1,0,1,0,1},
                                {1,0,34,0,1,1,1,34,1,1,1,0,1,0,1},
                                {1,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
                                {1,0,1,1,20,1,1,1,1,1,1,1,1,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,20,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第四层。
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
    ui->label_num_EXP->setText(QString::number(Superman.EXP));
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
                case 70:pix.load(":/mota/pictures/downstairs.bmp");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 71:pix.load(":/mota/pictures/upstairs.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
                case 80:pix.load(":/mota/pictures/merchant.png");
                        p.drawPixmap(250+50*j,14+50*i,50,50,pix);
                        break;
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
    if (map[j][i]/10==3)
    {
        if(!fight(map[j][i]%10))
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
        if(map[j][i]==62) {Superman.MAX_HP+=20;}
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
    if(map[j][i]==80)
    {
        shopping();
        return;
    }
    map[j][i]=4;
    Superman.X=i;
    Superman.Y=j;
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
            Superman.Y=13;
            Superman.floor=3;
            break;
           }
    case 4:{Superman.X=1;
            Superman.Y=1;
            Superman.floor=4;
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
             Superman.Y=0;
             Superman.floor=3;
             break;
            }
    }
    map[Superman.Y][Superman.X]=4;
}

bool Map::fight(int n)
{
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
         int k=(Mon[n].atk-Superman.Damage_Redu-Superman.defense);
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
         Superman.EXP+=Mon[n].EXP;
         Superman.level_up();
         return true;
        }
}

void Map::shopping()
{
    Shop.getgold(Superman.golden);
    Shop.grabKeyboard();
    Shop.show();
    Shop.releaseKeyboard();
}

void Map::getit()
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
        case 3:{Superman.MAX_HP+=20;
                Superman.HP+=20;
               }
               break;
        case 4:{Superman.atk+=6;
                Superman.Crit+=0.1;
               }break;
        case 5:{Superman.atk+=8;
                Superman.Feed_on_Blood+=0.05;
               }break;
        case 6:Superman.atk+=16;
               break;
        case 7:{Superman.atk+=35;
                Superman.Crit+=0.5;
                Superman.Crit_damage+=0.25;
               }break;
        case 8:{Superman.Double_hit=1;
                Superman.atk+=25;
                Superman.Crit+=0.3;
                Superman.Crit_damage+=0.2;
               }break;
        case 9:{Superman.atk+=40;
                Superman.Feed_on_Blood+=0.32;
               }break;
        case 10:{Superman.MAX_HP+=120;
                 Superman.HP+=120;
                 Superman.Damage_Redu+=10;
                }break;
        case 11:{Superman.MAX_HP+=200;
                 Superman.HP+=200;
                 Superman.HP_Rec+=0.02;
                }break;
    }
    Superman.golden-=Shop.mer[Shop.num][2].toInt();
    update();
}
