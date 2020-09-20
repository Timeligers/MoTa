#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>

class shop:public QWidget
{
    Q_OBJECT
public:
    explicit shop(QWidget *parent=nullptr);

    void keyReleaseEvent(QKeyEvent*event);
    void paintEvent(QPaintEvent*);

    void getgold(int gold);
    void buy();

    int Gold;
    int num;//选择的商品编号。

    QLabel *pus[12][3];
    QLabel *arrow;//箭头。
    QLabel *mygold;
    QLabel *conversation;
    QString mer[12][3]={{"商品名称","效果","所需金币"},
                        {"小红药","恢复10点HP","20"},
                        {"大红药","恢复25点HP","50"},
                        {"红宝石","+20点最大生命值","150"},
                        {"拳击手套","+6点攻击力，+10%暴击率","300"},
                        {"噬魂匕首","+8点攻击力，+5%吸血","325"},
                        {"青铜剑","+16点攻击力","300"},
                        {"光明圣剑","+35点攻击力，+50%暴击率，+25%暴击伤害","2260"},
                        {"速发弩箭","获得连击，+25点攻击力，30%暴击率，20%暴击伤害","2600"},
                        {"贪婪权杖","+40点攻击力，+32%吸血","2000"},
                        {"骑士银甲","+120点最大生命值，每次受到伤害时减免10点伤害","1900"},
                        {"圣光石","+200点最大生命值，每次移动恢复2%已损失的生命值","2600"},
                       };

    QTimer *timer;

signals:
    void saleit();

private slots:
    void arrow_ShoworHide();
};

#endif // SHOP_H
