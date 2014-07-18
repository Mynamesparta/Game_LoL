#ifndef CHAMPION_H
#define CHAMPION_H
#include <QGraphicsItem>
#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QPainter>
#include <QTime>
#include <QApplication>
#include "Worlds/World_of_Const.h"
class Champion:public QGraphicsItem
{
public:
    Champion(QString NameOfChampion);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* ppainter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*);
    virtual void First_skill();
    virtual void Second_skill();
    virtual void Third_skill();
    virtual void Fourth_skill();
    void move(float x, float y);
    void end_move(float x, float y);
private:
    QString NameOfChampion;
    QRegExp qreAnimation;
    QRegExp qreAnimationName;
    QTime qTimerforAnimation;
    QVector<QPixmap> qvAnimation_Stand;
    QVector<QPixmap> qvAnimation_Start_move;
    QVector<QPixmap> qvAnimation_Move;
    QVector<QPixmap> qvAnimation_End_move;
    QVector<QPixmap> qvAnimation_Autoattacks;
    QVector<QPixmap>::iterator qviAnimation_Stand;
    QVector<QPixmap>::iterator qviAnimation_Start_move;
    QVector<QPixmap>::iterator qviAnimation_Move;
    QVector<QPixmap>::iterator qviAnimation_End_move;
    QVector<QPixmap>::iterator qviAnimation_Autoattacks;
    float current_X=0;
    float current_Y=0;
    float angle;
    float dx,dy,l;
    float sqrt_sizeofpixmap;
    bool isTimeToChangeMoveAnimation=1;
    QPixmap* current_pixmap;
    World_of_const::Animation_state stateofAnimation;
};

#endif // CHAMPION_H
