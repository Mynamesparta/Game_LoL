#include "wall.h"

Map::Map(): qreForFile("_([0-9]+),([0-9]+)_ ([0-9 ]+)"),file("Resources/Wall.txt")
{
    file.open(QIODevice::ReadOnly);
    if(!file.exists())
    {
        qDebug()<<"We lost fill Wall.txt :(";
                  return;
    }
    QString str;
    QPoint point;
    bool b=0;
    //
    while(!file.atEnd())
    {
        str=file.readLine();
        //qDebug()<<"wall.cpp: str="<<str;
        if(str.contains(qreForFile))
        {
            wall[++maxIndexofWall]=new Wall;
            wall[maxIndexofWall]-> KingsPoint.setX(qreForFile.cap(1).toInt());
            wall[maxIndexofWall]-> KingsPoint.setY(qreForFile.cap(2).toInt());

            wall[maxIndexofWall]->Radius=0;
            QStringList stlist=qreForFile.cap(3).split(" ");
            b=0;
            while(stlist.length()>0)
            {
                str=stlist.takeFirst();
                if(b)
                {
                    point.setY(str.toInt());
                    wall[maxIndexofWall]->vectorforPoint<<point;
                    b=0;
                    l=length(wall[maxIndexofWall]->KingsPoint,point);
                    if(wall[maxIndexofWall]->Radius<l)
                    {
                        wall[maxIndexofWall]->Radius=l;
                        if(l>maxRadius)
                        {
                            maxRadius=l;
                            qDebug()<<"wall.cpp:l="<<l<<" |"<<wall[maxIndexofWall]->KingsPoint<<point;
                        }
                    }
                }
                else
                {
                    b=1;
                    point.setX(str.toInt());
                }
            }
        }
    }
    file.close();
}

Map::~Map()
{
    for(i=0;i<=maxIndexofWall;i++)
    {
        delete wall[i];
    }
}

bool Map::isWall(Point& currentPoint,int radius)
{
    Index=0;i=maxIndexofWall/2;
    maxRadius+=radius;
    while(i>1)
    {
        Index+=i;
        if(wall[Index]->KingsPoint.x()<currentPoint.x)
        {
            i=i/2;
            continue;
        }
        if(wall[Index]->KingsPoint.x()>currentPoint.x)
        {
            Index-=i;
            i=i/2;
            continue;
        }
        if(wall[Index]->KingsPoint.x()==currentPoint.x)
        {
            break;
        }
    }
    vectorforwall.clear();
    for(i=Index;i>=0;i--)
    {
        if(currentPoint.x - wall[i]->KingsPoint.x()<maxRadius)
        {
            dy=currentPoint.y - wall[i]->KingsPoint.y();
            if((dy>=0?dy:-dy)<maxRadius)
            {
                vectorforwall<<wall[i];
                //qDebug()<<"wall.cpp:"<<wall[i]->KingsPoint<<":KingsPoint("<<i<<")";
            }
        }
        else break;
    }
    for(i=Index+1;i<=maxIndexofWall;i++)
    {
        if(wall[i]->KingsPoint.x()-currentPoint.x <maxRadius)
        {
            dy=currentPoint.y - wall[i]->KingsPoint.y();
            if((dy>=0?dy:-dy)<maxRadius)
            {
                vectorforwall<<wall[i];
                //qDebug()<<"wall.cpp: "<<wall[i]->KingsPoint<<":KingsPoint("<<i<<")";
            }
        }
        else break;
    }
    maxRadius-=radius;
    while(vectorforwall.length())
    {
        _wall=vectorforwall.takeFirst();
        //qDebug()<<"wall.cpp: length"<<vectorforwall.length();
        if(length(currentPoint,_wall->KingsPoint)<_wall->Radius)
        {
            qDebug()<<"wall.cpp: Kings point="<<_wall->KingsPoint<<" pos="<<currentPoint.x<<","<<currentPoint.y;
            iteratorforPoint2=_wall->vectorforPoint.begin();
            l=_wall->Radius;
            for(;iteratorforPoint2<_wall->vectorforPoint.end();iteratorforPoint2++)
            {
                dx=length(currentPoint,*iteratorforPoint2);
                if(dx<l)
                {
                    l=dx;
                    point2=*iteratorforPoint2;
                    iteratorforPoint1=iteratorforPoint2;
                }
            }
            if(iteratorforPoint1==_wall->vectorforPoint.begin())
            {
                iteratorforPoint1=_wall->vectorforPoint.end();
                iteratorforPoint1--;
                point1=*iteratorforPoint1;
                iteratorforPoint1=_wall->vectorforPoint.begin();
            }
            else
            {
                iteratorforPoint1--;
                point1=*iteratorforPoint1;
                iteratorforPoint1++;
            }
            iteratorforPoint1++;
            if(iteratorforPoint1==_wall->vectorforPoint.end())
            {
                point3=*_wall->vectorforPoint.begin();
                iteratorforPoint1--;
            }
            else
            {
                point3=*iteratorforPoint1;
                iteratorforPoint1--;
            }

            bool b=0;
            if(d_length(point1,point2,currentPoint,_wall->KingsPoint,radius))
            {
                move_along_wall(currentPoint);
                b=1;
            }


            if(d_length(point3,point2,currentPoint,_wall->KingsPoint,radius))
            {
                move_along_wall(currentPoint);
                b=1;
            }
        }
    }
    return 0;
}
float Map::length(Point point1,QPoint point2)
{
    float dx=point1.x-point2.x();
    float dy=point1.y-point2.y();
    return sqrt(dx*dx+dy*dy);
}
float Map::length(Point point1,Point point2)
{
    float dx=point1.x-point2.x;
    float dy=point1.y-point2.y;
    return sqrt(dx*dx+dy*dy);
}
float Map::length(QPoint point1,QPoint point2)
{
    float dx=point1.x()-point2.x();
    float dy=point1.y()-point2.y();
    return sqrt(dx*dx+dy*dy);
}
bool Map::d_length(QPoint A, QPoint B, Point M,QPoint KingsPoint,int radius)
{
    if(B.y()<A.y())
    {
        point1=B;
        B=A;
        A=point1;

    }
    dx=B.x()-A.x();
    dy=B.y()-A.y();
    dx_dy=dx/dy;
    y=-(M.x-A.x())*dx_dy+A.y();
    /*qDebug()<<"wall.cpp: M.x="<<M.x<<" M.x-A.x()="<<M.x-A.x()<<" (M.x-A.x())*dx_dy="<<(M.x-A.x())*dx_dy<<" y="<<y;
    qDebug()<<"dx="<<dx<<" dy="<<dy;
    qDebug()<<A<<B;*/
    if(y>M.y)
    {
        l=length(M,A);
        if(l<radius)
        {
            x=A.x();
            y=A.y();
        }
        else return 0;
    }
    else
    {
        y=-(M.x-B.x())*dx_dy+B.y();
        if(y <M.y)
        {
            l=length(M,B);
            if(l<radius)
            {
                x=B.x();
                y=B.y();
            }
            else return 0;
        }
        else
        {
            l=(float)(M.x*(dy)+ M.y*(-dx)+(A.x()*(-dy)+A.y()*(dx)));
            l=l/length(A,B);
            if(!((l>=0?l:-l)<radius))
            {
                return 0;
            }
            x=(M.y-A.y()+M.x*(dx_dy)+A.x()/(dx_dy))/(dx_dy+1/dx_dy);
            y=(x-A.x())/dx_dy+A.y();
        }
    }
    dx=M.x-x;
    dy=M.y-y;
    l=sqrt(dx*dx+dy*dy);
    l=((float)radius)/l;
    if(sign(A,B,M,KingsPoint)==-1)
    {
        x=x+l*dx;
        y=y+l*dy;
    }
    else
    {
        x=x-l*dx;
        y=y-l*dy;
    }
    return 1;
}

int Map::sign(QPoint point1, QPoint point2, Point currentPoint,QPoint KingsPoint)
{
    int dx=point2.x()-point1.x();
    int dy=point2.y()-point1.y();
    int l;
    l=(float)(currentPoint.x*(dy)+ currentPoint.y*(-dx)+(point1.x()*(-dy)+point1.y()*(dx)));
    l=(l>=0?1:-1)*(float)(KingsPoint.x()*(dy)+ KingsPoint.y()*(-dx)+(point1.x()*(-dy)+point1.y()*(dx)));
    return (l>=0?1:-1);
}

void Map::move_along_wall(Point& M)
{
    M.x=x;
    M.y=y;
}
