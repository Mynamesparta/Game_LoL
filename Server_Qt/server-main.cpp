//#include ""
#include "Server/server.h"
#include "Server/ingame.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    Server server(9999);
    server.show();
    return app.exec();
}

void QObject::TimeEvent(QTimerEvent *)
{

}
