#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include "mainrole.h"
#include "monsters.h"
#include "shop.h"
#include <QGraphicsScene>
#include <QPixmap>

namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    void paintEvent(QPaintEvent*);
    void mainrole_faceup(QPixmap pix,QPainter &p);
    void printmap(QPainter &p);
    void printdata();

    void keyReleaseEvent(QKeyEvent* event);
    void move(int i, int j);

    void upstair(int floor);
    void downstair(int floor);

    void shopping();

    QVector<int> get_monster_list();

    mainrole Superman;
    monsters Mon[22];

    shop Shop;

    //单次战斗数据。
    int a;//暴击次数。
    int b;//战斗恢复量。
    int c;//总伤害量
    int f1;//战斗标志。
    int i_atk;
    int m_hp;
    int n_mon1;

    int keys[3];
    int face_up;
    int map[15][15];
    int in;
    int jn;

private:
    Ui::Map *ui;
    QPixmap *pix1;
    QTimer *battleTimer;
    QTimer *getItem;
    bool fightWin;
    int monsterFight;
    bool battleStart;
    int getItemNum;
    bool getStart;
    bool keyLFlag;


public slots:
    void getit();
    void fight();
    void getItem_screen();
    void saveDoc();
    void loadDoc();
    void initial();

};

#endif // MAP_H
