#ifndef WALL_H
#define WALL_H

#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QPoint>
#include "Server/ingame.h"
#include "Worlds/World_of_Const.h"
#include "Worlds/World_of_Struct.h"
class Point;
class Summoner;
struct Wall;
class Map
{
public:
    Map();
    ~Map();
    bool isWall(Point& currentPoint, int radius);
    float length(Point point1, QPoint point3);
    float length(Point point1,Point point3);
    float length(QPoint point1,QPoint point3);
    Summoner* summoner[World_of_const::N];
    int maxIndexofUser;
private:
    bool d_length(QPoint point1, QPoint point3, Point point, QPoint KingsPoint, int radius, bool b=0);
    int sign(QPoint point1,QPoint point3,Point currentPoint,QPoint KingsPoint);
    void move_along_wall(Point& M);
    QRegExp qreForFile;
    Wall* wall[10000];
    QFile file;
    float l;
    float dx;
    float x;
    float dy;
    float y;
    float dx_dy;
    int Index;
    int i;
    int maxIndexofWall=-1;
    float maxRadius=0;
    QVector<Wall*> vectorforwall;
    QVector<QPoint>::iterator iteratorforPoint1;
    QVector<QPoint>::iterator iteratorforPoint2;
    QPoint point1;
    QPoint point2;
    QPoint point3;
    Wall* _wall;
};
struct Wall
{
public:
    QVector<QPoint> vectorforPoint;
    QPoint KingsPoint;
    float Radius;
};

#endif // WALL_H
