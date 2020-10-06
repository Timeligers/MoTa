#include "map.h"
#include "ui_map.h"
#include "monsterlist.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <algorithm>
//这是存储基本地图数据的数组，我们用不同的Int值来代表地图上不同的Item
//第一层。0代表空位，1代表墙，2X代表门，3/4X代表怪物，4代表主角，5X代表钥匙，6X代表道具，70表示下楼，71表示上楼，72代表商店，80/1代表怪物。
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
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
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
                                {1,60,31,32,0,1,0,0,32,0,0,22,34,71,1},
                                {1,31,0,0,32,20,0,50,0,0,0,1,1,1,1},
                                {1,0,32,31,61,1,33,0,0,0,0,0,33,0,1},
                                {1,31,1,1,1,1,1,1,21,1,1,1,1,1,1},
                                {1,0,1,52,50,50,50,1,32,1,33,0,60,61,1},
                                {1,0,1,52,51,51,51,20,0,21,32,0,60,61,1},
                                {1,32,1,1,1,1,1,1,0,1,1,1,1,1,1},
                                {1,0,1,33,32,32,0,0,41,0,0,0,32,0,1},
                                {1,60,1,1,1,1,1,1,0,1,1,1,1,1,1},
                                {1,0,1,61,33,32,31,20,0,21,38,62,1,70,1},
                                {1,0,1,60,33,32,31,1,32,1,0,63,1,0,1},
                                {1,31,1,1,1,1,1,1,1,1,1,1,1,0,1},
                                {1,0,0,61,0,0,0,31,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第三层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {70,0,0,60,0,32,0,0,31,0,0,32,0,0,1},
                                {1,1,1,1,1,1,21,1,1,1,1,1,1,0,1},
                                {1,50,0,34,0,0,52,0,32,0,51,0,1,0,1},
                                {1,30,1,1,1,1,1,1,1,1,1,0,34,0,1},
                                {1,61,1,0,34,0,21,0,0,0,1,32,1,0,1},
                                {1,0,1,0,1,22,1,1,1,0,1,0,1,30,1},
                                {1,31,1,32,1,0,35,71,1,34,1,21,1,0,1},
                                {1,0,1,0,1,0,1,1,1,51,1,33,1,0,1},
                                {1,32,34,0,1,30,0,0,61,0,1,32,1,0,1},
                                {1,0,1,0,1,1,1,1,34,1,1,33,1,0,1},
                                {1,32,1,0,33,0,0,31,0,0,50,0,1,0,1},
                                {1,0,1,1,20,1,1,1,1,1,1,1,1,0,1},
                                {1,33,0,50,0,33,0,0,33,0,0,20,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第四层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,60,0,35,33,1,63,1,62,1,62,63,51,38,1},
                                {1,0,34,0,0,1,36,71,37,1,62,61,52,41,1},
                                {1,0,33,0,32,1,0,1,0,1,1,1,1,20,1},
                                {1,0,0,51,35,1,0,1,0,1,61,0,35,0,1},
                                {1,20,1,0,1,1,0,1,0,1,1,33,1,21,1},
                                {1,0,1,32,0,1,0,1,0,1,0,0,1,0,1},
                                {1,34,1,0,34,0,0,1,0,0,32,0,1,33,1},
                                {1,0,1,0,0,0,0,22,0,33,0,0,1,32,1},
                                {1,0,1,1,1,1,34,1,35,1,1,1,1,0,1},
                                {1,33,0,1,0,1,0,1,0,1,0,1,34,0,1},
                                {1,0,0,21,0,1,1,1,1,1,0,20,0,0,1},
                                {1,32,34,1,0,0,0,0,0,0,0,1,35,0,1},
                                {1,0,72,1,1,1,70,0,0,1,1,1,52,61,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第五层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,60,62,60,1,51,52,50,1,0,52,0,1,71,1},
                                {1,60,63,60,1,51,52,50,1,37,0,38,1,40,1},
                                {1,0,39,0,1,0,39,0,1,0,39,0,1,0,1},
                                {1,36,0,37,1,0,0,37,1,37,0,37,1,0,1},
                                {1,37,0,0,1,35,39,0,1,36,0,0,1,61,1},
                                {1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
                                {1,0,36,0,1,39,0,0,1,34,0,37,1,37,1},
                                {1,37,0,61,1,60,0,37,1,0,0,35,1,0,1},
                                {1,36,0,39,1,35,0,0,1,0,34,0,1,0,1},
                                {1,0,37,36,1,0,0,37,1,39,0,0,1,0,1},
                                {1,1,22,1,1,1,20,1,1,1,20,1,1,0,1},
                                {1,0,0,52,0,0,0,35,0,0,0,50,37,0,1},
                                {1,70,0,0,0,36,50,51,0,61,0,0,0,36,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第六层
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,60,0,39,0,42,0,71,0,43,0,61,60,0,1},
                                {1,39,0,40,0,0,1,0,1,39,0,1,0,0,1},
                                {1,1,0,0,0,39,1,41,1,61,0,1,38,40,1},
                                {1,61,1,0,39,0,1,0,1,0,0,1,1,21,1},
                                {1,0,40,0,51,0,1,0,1,39,40,1,39,0,1},
                                {1,0,0,1,0,37,1,0,1,0,0,1,39,0,1},
                                {1,40,0,52,1,0,1,60,1,39,0,22,0,60,1},
                                {1,52,0,0,39,1,1,0,1,0,0,1,0,52,1},
                                {1,0,39,0,1,62,1,39,1,1,1,1,1,0,1},
                                {1,0,37,0,21,38,1,0,1,0,0,0,1,39,1},
                                {1,40,0,37,1,1,1,0,1,0,1,37,1,37,1},
                                {1,0,39,37,1,0,0,0,0,0,1,0,1,0,1},
                                {1,37,0,0,0,0,0,70,0,0,1,0,50,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第七层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,41,0,20,0,0,70,0,0,21,0,40,0,1},
                                {1,40,0,52,1,0,0,0,0,0,1,40,41,39,1},
                                {1,1,20,1,1,1,1,22,1,1,1,1,20,1,1},
                                {1,0,0,0,1,40,0,39,0,40,1,0,0,39,1},
                                {1,60,41,0,22,0,0,0,40,0,21,0,41,50,1},
                                {1,0,42,40,1,0,41,0,0,51,1,52,0,0,1},
                                {1,1,20,1,1,1,1,21,1,1,1,1,20,1,1},
                                {1,39,41,0,41,1,39,0,52,1,0,0,41,42,1},
                                {1,0,40,40,0,20,0,42,41,21,40,0,60,0,1},
                                {1,38,0,42,61,1,40,0,39,1,0,42,0,0,1},
                                {1,1,1,21,1,1,1,22,1,1,1,20,1,1,1},
                                {1,63,0,50,51,1,0,43,0,1,52,0,0,62,1},
                                {1,63,0,50,51,1,0,71,0,1,52,0,0,62,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第八层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,62,0,46,1,0,1,71,1,0,1,47,0,60,1},
                                {1,0,49,0,1,0,1,80,1,0,1,0,48,0,1},
                                {1,48,45,0,1,0,1,22,1,0,1,0,45,0,1},
                                {1,1,22,1,1,0,0,0,0,0,1,1,21,1,1},
                                {1,0,45,0,43,0,45,0,0,0,45,0,43,0,1},
                                {1,0,51,0,60,44,0,0,44,0,43,0,0,61,1},
                                {1,44,0,45,0,0,44,0,0,0,45,44,0,52,1},
                                {1,0,43,0,0,44,0,0,43,0,52,44,0,0,1},
                                {1,72,0,44,0,51,0,45,0,44,0,0,50,0,1},
                                {1,1,1,1,1,0,0,0,0,0,1,1,1,1,1},
                                {1,0,52,43,1,0,0,0,0,0,1,45,0,50,1},
                                {1,0,46,0,20,0,0,0,0,0,20,0,47,0,1},
                                {1,51,45,44,1,0,0,70,0,0,1,0,44,45,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},//第九层。
                               {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,78,0,0,0,0,0,70,0,0,0,0,0,78,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,1,1,1,1,22,1,1,1,1,0,0,1},
                                {1,0,0,1,0,0,0,79,0,0,0,1,0,0,1},
                                {1,0,0,1,0,1,1,22,1,1,0,1,0,0,1},
                                {1,0,0,1,0,1,0,0,0,1,0,1,0,0,1},
                                {1,0,0,1,0,1,0,81,0,1,0,1,0,0,1},
                                {1,0,0,1,0,1,0,0,0,1,0,1,0,0,1},
                                {1,0,0,1,0,1,1,1,1,1,0,1,0,0,1},
                                {1,0,0,1,61,61,63,62,63,61,61,1,0,0,1},
                                {1,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,78,0,0,0,0,0,0,0,0,0,0,0,78,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}//第十层。
                              };

Map::Map(QWidget *parent) ://一些初始化的工作
    QMainWindow(parent),
    ui(new Ui::Map)
{
    this->setFixedSize(1000,764);
    ui->setupUi(this);
    for(int ii=0;ii<3;ii++)
    {
        keys[ii]=0;
    }
    memcpy(map,floors[0],900);
    Superman.X=1;
    Superman.Y=1;
    Superman.floor=1;
    map[Superman.Y][Superman.X]=4;
    face_up=3;
    ui->listUI->hide();
    ui->battleScreen->hide();
    ui->item_get->hide();
    pix1=new QPixmap(":/mota/pictures/down_00.png");
    pix1->scaled(ui->imgSuperman->size(), Qt::KeepAspectRatio);
    ui->imgSuperman->setScaledContents(true);
    ui->imgSuperman->setPixmap(*pix1);
    delete pix1;
    battleTimer=new QTimer(this);
    getItem=new QTimer(this);
    battleStart=false;
    getStart=false;
    fightWin=false;

    getItemNum=0;
    keyLFlag=false;
    for(int i1=0;i1<=21;++i1){
        Mon[i1].mon(i1);
    }
    connect(battleTimer, SIGNAL(timeout()), this, SLOT(fight()));
    connect(getItem, SIGNAL(timeout()), this, SLOT(getItem_screen()));
    connect(&Shop,SIGNAL(saleit()),this,SLOT(getit()));
    connect(ui->saveBtn, &QPushButton::clicked, this, &Map::saveDoc);
    connect(ui->loadBtn, &QPushButton::clicked, this, &Map::loadDoc);
    connect(ui->initialBtn, &QPushButton::clicked, this, &Map::initial);
}

Map::~Map()
{
    delete ui;
}

//虚函数，绘图用函数，每次调用update()函数即可刷新基本界面
void Map::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.save();
    printmap(p);
    p.restore();

    printdata();
}
//绘图函数的一部分，展示主角属性
void Map::printdata()
{
    ui->label_num_HP->setText(QString::number(Superman.HP)+"/"+QString::number(Superman.MAX_HP));
    ui->label_num_ATK->setText(QString::number(Superman.atk));
    ui->label_num_Def->setText(QString::number(Superman.defense));
    ui->label_num_EXP->setText(QString::number(Superman.EXP)+"/"+QString::number(Superman.EXP_To_LevelUP));
    ui->label_num_Level->setText(QString::number(Superman.Level));
    ui->label_num_golden->setText(QString::number(Superman.golden));
    ui->label_num_yellow_key->setText(QString::number(keys[0]));
    ui->label_num_blue_key->setText(QString::number(keys[1]));
    ui->label_num_red_key->setText(QString::number(keys[2]));
}
//绘图函数的一部分，绘制基本图形界面
void Map::printmap(QPainter &p)
{
    QPixmap pix;
    pix.load(":/mota/pictures/background.bmp");
    p.drawPixmap(0,14,1000,750,pix);
    for(int ii=0;ii<15;ii++)
        for(int j=0;j<15;j++)
        {
            switch (map[ii][j])
            {
                case 1:pix.load(":/mota/pictures/wall.bmp");
                       p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                       break;
                case 4:mainrole_faceup(pix,p);
                       break;
                case 20:pix.load(":/mota/pictures/yellow_door.bmp");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 21:pix.load(":/mota/pictures/blue_door.bmp");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 22:pix.load(":/mota/pictures/red_door.bmp");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 30:pix.load(":/mota/pictures/monster_00.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 31:pix.load(":/mota/pictures/monster_01.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 32:pix.load(":/mota/pictures/monster_02.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 33:pix.load(":/mota/pictures/monster_03.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 34:pix.load(":/mota/pictures/monster_04.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 35:pix.load(":/mota/pictures/monster_05.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 36:pix.load(":/mota/pictures/monster_06.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 37:pix.load(":/mota/pictures/monster_07.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 38:pix.load(":/mota/pictures/monster_08.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 39:pix.load(":/mota/pictures/monster_09.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 40:pix.load(":/mota/pictures/monster_10.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 41:pix.load(":/mota/pictures/monster_11.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 42:pix.load(":/mota/pictures/monster_12.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 43:pix.load(":/mota/pictures/monster_13.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 44:pix.load(":/mota/pictures/monster_14.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 45:pix.load(":/mota/pictures/monster_15.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 46:pix.load(":/mota/pictures/monster_16.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 47:pix.load(":/mota/pictures/monster_17.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 48:pix.load(":/mota/pictures/monster_18.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 49:pix.load(":/mota/pictures/monster_19.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 50:pix.load(":/mota/pictures/yellow_key.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 51:pix.load(":/mota/pictures/blue_key.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 52:pix.load(":/mota/pictures/red_key.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 60:pix.load(":/mota/pictures/small_medcine.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 61:pix.load(":/mota/pictures/big_medcine.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 62:pix.load(":/mota/pictures/red_stone.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;//修改！！！！
                case 63:pix.load(":/mota/pictures/blue_stone.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;//修改！！！！
                case 70:pix.load(":/mota/pictures/downstairs.bmp");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 71:pix.load(":/mota/pictures/upstairs.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 72:pix.load(":/mota/pictures/merchant.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 80:pix.load(":/mota/pictures/monster_20.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
                case 81:pix.load(":/mota/pictures/boss.png");
                        p.drawPixmap(250+50*j,14+50*ii,50,50,pix);
                        break;
            }
        }
}
//printmap函数的一部分，负责主角朝向
void Map::mainrole_faceup(QPixmap pix, QPainter &p)
{
    int ii=Superman.X,j=Superman.Y;
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
    p.drawPixmap(250+50*ii,14+50*j,50,50,pix);

}
//键盘事件，控制上下左右移动，以及“L”键显示怪物列表
//两个bool值battlestart和getstart确保在战斗界面和拾取界面时主角不会随意移动
void Map::keyReleaseEvent(QKeyEvent* event)
{
    this->grabKeyboard();
    if(event->key()==Qt::Key_Left)
    {
        if(battleStart==false&&getStart==false){
            face_up=4;
            move(Superman.X-1,Superman.Y);

        }
    }
    else if(event->key()==Qt::Key_Right)
    {
        if(battleStart==false&&getStart==false){
            face_up=2;
            move(Superman.X+1,Superman.Y);

        }
    }
    else if(event->key()==Qt::Key_Up)
    {
        if(battleStart==false&&getStart==false){
            face_up=1;
            move(Superman.X,Superman.Y-1);

        }
    }
    else if(event->key()==Qt::Key_Down)
    {
        if(battleStart==false&&getStart==false){
            face_up=3;
            move(Superman.X,Superman.Y+1);

        }
    }
    else if(event->key()==Qt::Key_L){ //查看怪物手册
        if(keyLFlag==false){

           MonsterList* monstor_list = new MonsterList(ui->listUI);

           monstor_list->setFixedSize(761,791);

           QVector<int> monster_id_list = get_monster_list();

           for(auto it= monster_id_list.begin(); it != monster_id_list.end(); ++it)
               monstor_list->addItem(*it, Superman, Mon);
           ui->listUI->show();
           keyLFlag=true;
        }
        else{
            ui->listUI->hide();
            keyLFlag=false;
        }
   }
   update();
}

//获取当前层数的怪物列表，使用标准库中的函数排序和去重，返回一个一维 Int型Qvector
   QVector<int> Map::get_monster_list()
   {
       QVector<int> monster_id_list;
       for(int i1=0;i1<15;++i1){
           for(int i2=0;i2<15;++i2){
               if((map[i1][i2]>=30&&map[i1][i2]<=49)||map[i1][i2]==80||map[i1][i2]==81){
                   int index;
                   if(map[i1][i2]>=30&&map[i1][i2]<=49){
                       index=map[i1][i2]-30;
                   }
                   if(map[i1][i2]==80||map[i1][i2]==81){
                       index=map[i1][i2]-60;
                   }
                   monster_id_list.push_back(index);
               }
           }
       }
       std::sort(monster_id_list.begin(),monster_id_list.end());
       auto pos=std::unique(monster_id_list.begin(),monster_id_list.end());
       monster_id_list.erase(pos,monster_id_list.end());
       return monster_id_list;
   }

//移动所引起的事件触发函数
void Map::move(int i, int j)
{
    in=i;
    jn=j;
    if(map[jn][in]==1||(in<0||in>14)||(jn<0||jn>14))//撞墙
        return;
    if(map[jn][in]/10==2)//拿钥匙
    {
        if(keys[map[jn][in]%10]!=0)
        {
            keys[map[jn][in]%10]--;
            map[jn][in]=0;
            update();
        }
        return;
    }
    if (map[jn][in]/10==3||map[jn][in]/10==4||map[jn][in]==80||map[jn][in]==81)//战斗
    {
        monsterFight=map[jn][in];//后期又增加了一些怪物，所以怪物序列有割裂
        int num=monsterFight;
        if(num>=80)//编号20之后的怪物。
            n_mon1=num-60;
        else if(num<50)//编号20之前的怪物。
            n_mon1=num-30;
        Mon[n_mon1].mon(n_mon1);
        Mon[n_mon1].pix.scaled(ui->imgEnemy->size(), Qt::KeepAspectRatio);//战斗界面的一些准备
        ui->imgEnemy->setScaledContents(true);
        ui->imgEnemy->setPixmap(Mon[n_mon1].pix);
        ui->hpNum->setText(QString::number(Mon[n_mon1].HP));
        ui->atkNum->setText(QString::number(Mon[n_mon1].atk));
        ui->defNum->setText(QString::number(Mon[n_mon1].defense));
        ui->hpNum_2->setText(QString::number(Superman.HP));
        ui->atkNum_2->setText(QString::number(Superman.atk));
        ui->defNum_2->setText(QString::number(Superman.defense));
        m_hp=Mon[n_mon1].HP;
        i_atk=Superman.atk;//i:单次伤害;
        f1=1;//测试用数据，不参与用户交互
        a=0;
        b=0;
        c=0;
        battleStart=true;
        fightWin=false;
        ui->battleScreen->show();
        battleTimer->start(500);//主要基于Qtimer实现战斗界面，这里相当于发出了一个timeout()的信号
        return;
    }
    if(map[jn][in]/10==5)//拾取钥匙事件，同样主要基于Qtimer实现
    {
        getItemNum=map[jn][in];
        keys[getItemNum%10]++;
        map[jn][in]=0;
        update();
        getStart=true;
        if(getItemNum==50){
            ui->item_get->setText("获得黄钥匙");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 127);");
        }
        else if(getItemNum==51){
            ui->item_get->setText("获得蓝钥匙");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(0, 255, 255);");
        }
        else if(getItemNum==52){
            ui->item_get->setText("获得红钥匙");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 0, 127);");
        }
        ui->item_get->show();
        getItem->start(350);
        return;

    }  

    if(map[jn][in]/10==6)//相似地，拾取其他道具的事件
    {
        getItemNum=map[jn][in];
        map[jn][in]=0;
        update();
        getStart=true;
        if(getItemNum==60){
            Superman.HP+=10;
            ui->item_get->setText("获得10点生命");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        }
        if(getItemNum==61){
            Superman.HP+=25;
            ui->item_get->setText("获得25点生命");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        }
        if(getItemNum==62){
            Superman.atk+=3;
            ui->item_get->setText("获得3点攻击");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        }
        if(getItemNum==63){
            Superman.defense+=3;
            ui->item_get->setText("获得3点防御");
            ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
        }
        if(Superman.HP>Superman.MAX_HP)
            Superman.HP=Superman.MAX_HP;
        ui->item_get->show();
        getItem->start(350);
        return;
    }
    if(map[jn][in]==71)//上楼事件
    {
        upstair(Superman.floor);
        return;
    }
    if(map[jn][in]==70)//下楼事件
    {
        downstair(Superman.floor);
        return;
    }
    if(map[jn][in]==72)//商店购买事件
    {
        shopping();
        return;
    }
    map[jn][in]=4;
    Superman.X=in;
    Superman.Y=jn;
    if(Superman.HP_Rec>0)//商店中通过移动恢复生命的道具
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

void Map::fight()//战斗界面槽函数，整合了战斗界面以及具体战斗机制的实现
{

    srand((unsigned)time(nullptr));
        {if(rand()%100<Superman.Crit*100)
            {i_atk=int(Superman.atk*Superman.Crit_damage);
             a++;
            }
         if(Superman.Double_hit)
            {m_hp-=(i_atk-Mon[n_mon1].defense);
             if(m_hp<=0){
                 m_hp=0;
                 ui->hpNum->setText("0");

             }
            }
         int k=(Mon[n_mon1].atk-Superman.defense);
         if(k>0)
            Superman.HP-=k;
         if((Mon[n_mon1].defense-i_atk)<0)
         m_hp=m_hp+Mon[n_mon1].defense-i_atk;
         //如果通过暴击有希望杀死怪物，那么即使胜率再低也会进行对战
         //但如果毫无获胜希望，或者只能平局，也就是说互相刮痧，那么将不会进行战斗
         if((Mon[n_mon1].defense-Superman.atk*Superman.Crit_damage)>0){
             battleStart=false;
             ui->battleScreen->hide();
             battleTimer->stop();

             return;
         }
         c+=i_atk;
         Superman.HP+=i_atk*Superman.Feed_on_Blood;
         b+=i_atk*Superman.Feed_on_Blood;
         if(Superman.HP>Superman.MAX_HP)
            Superman.HP=Superman.MAX_HP;
         if(m_hp<0){
             m_hp=0;
         }
         if(Superman.HP<0){
             Superman.HP=0;
         }
         ui->hpNum->setText(QString::number(m_hp));
         ui->hpNum_2->setText(QString::number(Superman.HP));
        }
     if(Superman.HP<=0)//战败选择是读档还是重开
        {
         //战败。
         fightWin=false;
         battleStart=false;
         ui->battleScreen->hide();
         battleTimer->stop();
         QMessageBox::StandardButton btn;
         btn = QMessageBox::question(this, "注意", "冒险失败！是否读档？", QMessageBox::Yes|QMessageBox::No);
         if (btn == QMessageBox::Yes){
             Map::loadDoc();
         }
         else{
             Map::initial();
         }
         return;
        }
     else if(m_hp<=0)//胜利也会触发拾取事件
        {
         getItemNum=map[jn][in];
         fightWin=true;
         battleStart=false;
         ui->battleScreen->hide();
         battleTimer->stop();
         map[jn][in]=0;
         update();
         if((getItemNum>=30&&getItemNum<=49)||getItemNum==80||getItemNum==81){
             int prelevel=Superman.Level;
             Superman.golden+=Mon[n_mon1].golden;
             if(Superman.Level<20)
                Superman.EXP+=Mon[n_mon1].EXP;
             Superman.level_up();
             QString temp;
             temp="获得"+QString::number(Mon[n_mon1].golden)+"金币，"+QString::number(Mon[n_mon1].EXP)+"经验";
             ui->item_get->setStyleSheet("background-color: rgb(0, 0, 0);color: rgb(255, 255, 255);");
             if(prelevel<Superman.Level){
                 temp=temp+"\n升级啦！！！";
                 //好看的升级画面，用stylesheet设置渐变效果，语法格式可以直接从UI设计师界面复制粘贴，或者参考stylesheet的help网页
                 ui->item_get->setStyleSheet("color: rgb(0, 0, 0);"
                                             "background-color: qconicalgradient(cx:0, cy:0, angle:135, "
                                             "stop:0 rgba(255, 255, 0, 69), "
                                             "stop:0.375 rgba(255, 255, 0, 69), "
                                             "stop:0.423533 rgba(251, 255, 0, 145), "
                                             "stop:0.45 rgba(247, 255, 0, 208), "
                                             "stop:0.477581 rgba(255, 244, 71, 130), "
                                             "stop:0.518717 rgba(255, 218, 71, 130), "
                                             "stop:0.55 rgba(255, 255, 0, 255), "
                                             "stop:0.57754 rgba(255, 203, 0, 130), "
                                             "stop:0.625 rgba(255, 255, 0, 69), "
                                             "stop:1 rgba(255, 255, 0, 69));");
             }
             ui->item_get->setText(temp);

         }
         ui->item_get->show();
         getItem->start(600);
         if(getItemNum==81){//打败魔王游戏结束
             QMessageBox::StandardButton btn;
             btn = QMessageBox::question(this, "注意", "你打败了魔王！冒险结束了，是否读档？", QMessageBox::Yes|QMessageBox::No);
             if (btn == QMessageBox::Yes){
                 Map::loadDoc();
             }
             else{
                 Map::initial();
             }
         }
         return;
        }

}
//拾取事件的槽函数
void Map::getItem_screen(){
    getStart=false;
    getItem->stop();
    ui->item_get->hide();
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
            Superman.Y=11;
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
    case 6:{Superman.X=2;
                Superman.Y=13;
                Superman.floor=6;
                break;
               }
    case 7:{Superman.X=7;
                Superman.Y=12;
                Superman.floor=7;
                break;
               }
    case 8:{if(face_up==2)
                {
                    Superman.X=8;
                    Superman.Y=1;
                }
                if(face_up==4)
                {
                    Superman.X=6;
                    Superman.Y=1;
                }
                if(face_up==1)
                {
                    Superman.X=7;
                    Superman.Y=2;
                }
                Superman.floor=8;
                break;
               }
    case 9:{Superman.X=7;
                Superman.Y=12;
                Superman.floor=9;
                break;
               }
    case 10:{Superman.X=7;
                 Superman.Y=2;
                 Superman.floor=10;
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
             Superman.Y=1;
             Superman.floor=3;
             break;
            }
    case 4:{Superman.X=6;
            Superman.Y=7;
            Superman.floor=4;
            break;
           }
    case 5:{if(map[2][6]==4)
                {
                    Superman.X=6;
                    Superman.Y=2;
                }
                if(map[2][8]==4)
                {
                    Superman.X=8;
                    Superman.Y=2;
                }
                Superman.floor=5;
                break;
               }
    case 6:{Superman.X=13;
                Superman.Y=2;
                Superman.floor=6;
                break;
               }
    case 7:{if(face_up==2)
                {
                    Superman.X=8;
                    Superman.Y=1;
                }
                if(face_up==4)
                {
                    Superman.X=6;
                    Superman.Y=1;
                }
                if(face_up==3)
                {
                    Superman.X=7;
                    Superman.Y=2;
                    face_up=1;
                }
                Superman.floor=7;
                break;
               }
    case 8:{Superman.X=7;
                Superman.Y=12;
                Superman.floor=8;
                break;
               }
    case 9:{Superman.X=7;
                Superman.Y=2;
                Superman.floor=9;
                break;
               }
    }
    map[Superman.Y][Superman.X]=4;
}


void Map::shopping()
{
    Shop.init();
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
        case 3:Superman.defense+=4;
               break;
        case 4:{Superman.atk+=3;
                Superman.Crit+=0.1;
               }break;
        case 5:{Superman.atk+=4;
                Superman.Feed_on_Blood+=0.05;
               }break;
        case 6:Superman.atk+=6;
               break;
        case 7:{Superman.atk+=22;
                Superman.Crit+=0.5;
                Superman.Crit_damage+=0.25;
               }break;
        case 8:{Superman.Double_hit=1;
                Superman.atk+=18;
                Superman.Crit+=0.3;
                Superman.Crit_damage+=0.2;
               }break;
        case 9:{Superman.atk+=20;
                Superman.Feed_on_Blood+=0.32;
               }break;
        case 10:{Superman.MAX_HP+=250;
                 Superman.HP+=250;
                 Superman.defense+=22;
                }break;
        case 11:{Superman.MAX_HP+=400;
                 Superman.HP+=400;
                 Superman.defense+=16;
                 Superman.HP_Rec+=0.02;
                }break;
    }
    Superman.golden-=Shop.mer[Shop.num][2].toInt();
    update();
}

//下面三个是相似的存档，读档，和重新开始的槽函数，有确认对话框，通过QT封装好的Qfile和Qdatastream实现
void Map::saveDoc(){
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "注意", "是否确定存档?", QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes){
        memcpy(floors[Superman.floor-1],map,900);
        QFile file("history_file");
        file.open(QIODevice::WriteOnly|QIODevice::Truncate);
        QDataStream out(&file);
        int flo=10;//存地图信息
        for(int i1=0;i1<flo;++i1){
            for(int i2=0;i2<15;++i2){
                for(int i3=0;i3<15;++i3){
                    out<<floors[i1][i2][i3];
                }
            }
        }
        //存人物信息
        //qint32
        out<<Superman.atk;
        out<<Superman.defense;
        out<<Superman.HP;
        out<<Superman.MAX_HP;
        out<<Superman.golden;
        out<<Superman.Level;
        out<<Superman.EXP;
        out<<Superman.EXP_To_LevelUP;
        out<<Superman.floor;
        out<<Superman.X;
        out<<Superman.Y;
        out<<keys[0];
        out<<keys[1];
        out<<keys[2];
        out<<face_up;
        //qint8
        out<<Superman.Double_hit;
        //qreal
        out<<Superman.Crit_damage;
        out<<Superman.Crit;
        out<<Superman.Feed_on_Blood;
        out<<Superman.HP_Rec;

        out<<Shop.num;

    }

}

void Map::loadDoc(){
    QFile file_check("history_file");
    if(!file_check.exists()){
        file_check.close();
        QMessageBox::warning(this,"warning","暂无存档");
        return;
    }
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "注意", "是否确定读档?", QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes){
        QFile file("history_file");
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);    // read the data serialized from the file
        int flo=10;
        for(int i1=0;i1<flo;++i1){
            for(int i2=0;i2<15;++i2){
                for(int i3=0;i3<15;++i3){
                    in>>floors[i1][i2][i3];
                }
            }
        }
        //qint32
        in>>Superman.atk;
        in>>Superman.defense;
        in>>Superman.HP;
        in>>Superman.MAX_HP;
        in>>Superman.golden;
        in>>Superman.Level;
        in>>Superman.EXP;
        in>>Superman.EXP_To_LevelUP;
        in>>Superman.floor;
        in>>Superman.X;
        in>>Superman.Y;
        in>>keys[0];
        in>>keys[1];
        in>>keys[2];
        in>>face_up;
        //qint8
        in>>Superman.Double_hit;
        //qreal
        in>>Superman.Crit_damage;
        in>>Superman.Crit;
        in>>Superman.Feed_on_Blood;
        in>>Superman.HP_Rec;

        in>>Shop.num;

        memcpy(map,floors[Superman.floor-1],900);
        update();
        file.close();
    }

}

void Map::initial(){
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, "注意", "是否确定重新开始冒险?", QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes){
        QFile file("init");
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);    // read the data serialized from the file
        int flo=10;
        for(int i1=0;i1<flo;++i1){
            for(int i2=0;i2<15;++i2){
                for(int i3=0;i3<15;++i3){
                    in>>floors[i1][i2][i3];
                }
            }
        }
        //qint32
        in>>Superman.atk;
        in>>Superman.defense;
        in>>Superman.HP;
        in>>Superman.MAX_HP;
        in>>Superman.golden;
        in>>Superman.Level;
        in>>Superman.EXP;
        in>>Superman.EXP_To_LevelUP;
        in>>Superman.floor;
        in>>Superman.X;
        in>>Superman.Y;
        in>>keys[0];
        in>>keys[1];
        in>>keys[2];
        in>>face_up;
        //qint8
        in>>Superman.Double_hit;
        //qreal
        in>>Superman.Crit_damage;
        in>>Superman.Crit;
        in>>Superman.Feed_on_Blood;
        in>>Superman.HP_Rec;
        in>>Shop.num;
        memcpy(map,floors[Superman.floor-1],900);
        update();
        file.close();
    }
}












