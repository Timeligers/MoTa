#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include "mainrole.h"
#include "monsters.h"
#include "shop.h"

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
    void move(int i,int j);

    bool fight(int n);
    void upstair(int floor);
    void downstair(int floor);

    void shopping();

    mainrole Superman;
    monsters Mon[6];

    shop Shop;

    //单次战斗数据。
    int a;//暴击次数。
    int b;//战斗恢复量。
    int c;//总伤害量
    int f1;//战斗标志。

    int keys[3];
    int face_up;
    int map[15][15];

private:
    Ui::Map *ui;

public slots:
    void getit();
};

#endif // MAP_H
