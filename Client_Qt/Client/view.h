#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFile>
#include <QVector>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QScrollBar>
#include <QGraphicsEllipseItem>
#include "Worlds/World_of_Button.h"

enum MOUSE{PressLeft,PressRight,Move,Release,None};
class View:public QGraphicsView
{
public:
    View(QGraphicsScene *scene);
    ~View();

    MOUSE qpointMousePosition(QPoint& position);
    QString takeKey();
private:
    QPixmap qpMap;
    QPoint mouse_position;
    MOUSE stateofMouse=None;
    QString qsKey;
    QGraphicsScene *scene;
    bool isRelease=0;
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
};

#endif // VIEW_H
