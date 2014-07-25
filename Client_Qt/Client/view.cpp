#include "view.h"

View::View(QGraphicsScene* scene):QGraphicsView(scene),scene(scene),
    qpMap("Resources/window/Map.jpg")
{
    //file.open(QIODevice::ReadOnly);
    scene->addPixmap(qpMap)->setScale(4);
    show();
}

View::~View()
{

}
//====================Event================
void View::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        stateofMouse=PressLeft;
        mouse_position=QPoint(event->x()+ this->horizontalScrollBar()->value(),
                              event->y()+ this->verticalScrollBar()->value());
        return;
    }
    if(event->buttons()==Qt::RightButton)
    {
        stateofMouse=PressRight;
        mouse_position=QPoint(event->x()+ this->horizontalScrollBar()->value(),
                              event->y()+ this->verticalScrollBar()->value());
        return;
    }
}

void View::mouseMoveEvent(QMouseEvent* event)
{
    if(stateofMouse==Move)
    {
        mouse_position=QPoint(event->x()+ this->horizontalScrollBar()->value(),
                              event->y()+ this->verticalScrollBar()->value());
    }
}
void View::mouseReleaseEvent(QMouseEvent* event)
{
    mouse_position=QPoint(event->x()+ this->horizontalScrollBar()->value(),
                          event->y()+ this->verticalScrollBar()->value());
    isRelease=1;
}

void View::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==World_of_buttons::First_skill)
    {
        qsKey="skill_1";
        return;
    }
    if(event->key()==World_of_buttons::Second_skill)
    {
        qsKey="skill_2";
        return;
    }
    if(event->key()== World_of_buttons::Third_skill)
    {
        qsKey="skill_3";
        return;
    }
    if(event->key()==World_of_buttons::Fourth_skill)
    {
        qsKey="skill_4";
        return;
    }
}

//==================Information=================
MOUSE View::qpointMousePosition(QPoint& position)
{
    switch(stateofMouse)
    {
        case Move:
        {
            position=mouse_position;
            if(isRelease)
            {
                stateofMouse=Release;
            }
            return Move;
        }
        case Release:
        {
            position=mouse_position;
            isRelease=0;
            stateofMouse=None;
            return Release;
        }
        case None:
        {
            return None;
        }
        default:
        {
            position=mouse_position;
            MOUSE mouse=stateofMouse;
            if(isRelease)
            {
                stateofMouse=Release;
            }
            else stateofMouse=Move;
            return mouse;
        }
    }
}

QString View::takeKey()
{
    QString str=qsKey;
    qsKey="";
    return str;
}
