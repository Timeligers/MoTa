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

    void init();
    void hide();
    void getgold(int gold);
    void buy();

    int Gold;
    int num;//选择的商品编号。
    int c;
    int n;//商店剩余商品数量。

    QLabel *pus[12][3];
    QLabel *arrow;//箭头。
    QLabel *mygold;
    QLabel *conversation;
    QString mer[12][3]={{"商品名称","效果","所需金币"},
                        {"小红药","恢复10点HP","20"},
                        {"大红药","恢复25点HP","50"},
                        {"布甲","+4点防御","300"},
                        {"拳击手套","+3点攻击力，+10%暴击率","325"},
                        {"噬魂匕首","+4点攻击力，+5%吸血","350"},
                        {"青铜剑","+6点攻击力","330"},
                        {"光明圣剑","+22点攻击力，+50%暴击率，+25%暴击伤害","2260"},
                        {"速发弩箭","获得连击，+18点攻击力，30%暴击率，20%暴击伤害","2600"},
                        {"贪婪权杖","+20点攻击力，+32%吸血","2700"},
                        {"骑士银甲","+250点最大生命值，+22点防御","2500"},
                        {"圣光石","+400点最大生命值，+16点防御，每次移动恢复2%已损失的生命值","2800"},
                       };

    QTimer *timer;

signals:
    void saleit();

private slots:
    void arrow_ShoworHide();
};

#endif // SHOP_H

