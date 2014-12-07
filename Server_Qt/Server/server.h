#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QIODevice>
#include <QRegExp>
#include <QApplication>
#include <QVector>
#include "ingame.h"
#include "Worlds/World_of_Const.h"
#include "Encryption/rsa.h"
#include "Encryption/symmetric.h"
class QTcpServer;
class QTcpSocket;
class ClientsInfo;
class InGame;
class QSendToClientEvent;
class Lobby;
class RSA;
class Symmetric;
//struct rbw::PlayerExportInformation;
class Server : public QWidget
{
    Q_OBJECT
private:
    void sendToGame(int Index,const QString& str);

    QRegExp qreUserName;
    QRegExp qreCreateLobby;
    QRegExp qreContoLobby;
    QRegExp qreinLobbyChat;
    QRegExp qreinLobbyRSA;
    quint16 m_nNextBlockSize;
    QList<unsigned int> qlSearch;
    int maxIndexClintInfo=-1;
    QVector<Lobby*> ListofLobby;
    InGame *ingame[500];
    QTcpServer* qtcpServer;
    ClientsInfo* client[1000];

public:
    Server(int nPort,QWidget *parent = 0);
    void customEvent(QEvent* pe);
    ~Server();
public slots:
    void slotCreateGame();
    void slotinLobbyCreateGame();
    virtual void  slotNewConnection();
    void slotDisconnect();
    void slotReadClient();
    void sendToClient(QTcpSocket*,const QString&);
    void slotDestroyGame(int Index);
    void slotDeleteLobby();
//    void slotSendToClient(int);
signals:
};
//=====================================
enum State{Registration,Menu,SearchGame,inLobby,inGame};
class ClientsInfo:public QObject
{
    Q_OBJECT
private:
    QTcpSocket* qtcpSocket;
    int Win=0;
    int Lose=0;
    const int Index;
public:
    ClientsInfo(QTcpSocket* Socket,int i):Index(i)
    {
        qDebug()<<"Hello New Client["<<Index<<"].Welcome to HELL!";
        qtcpSocket=Socket;
        connect(Socket,SIGNAL(readyRead()),
                this,SLOT(slotReadyRead()));
        connect(Socket,SIGNAL(disconnected()),
                this,SLOT(slotDisconnected()));
    }
    QTcpSocket* Take_Socket()
    {
        return qtcpSocket;
    }
    ~ClientsInfo()
    {
    }
    int TakeInfo(const QString);
    void operator ++(int)
    {
        Win++;
    }
    void operator --(int)
    {
        Lose++;
    }
    void operator ++()
    {
        Win++;
    }
    void operator --()
    {
        Lose++;
    }
    QString UserName="";
    int Match=-1;
    int IndexInGame=-1;
    Lobby* lobby=NULL;
    enum State state=Registration;
signals:
    void sig_ReadyRead();
    void sig_Disconnected();
private slots:
    void slotReadyRead()
    {
        sig_ReadyRead();
    }
    void slotDisconnected()
    {
        sig_Disconnected();
    }
};
//============Lobby===============
class Lobby:public QObject
{
    Q_OBJECT
private:
    static bool TimeToEncryption;
    void SendNameOfKing(ClientsInfo* client);
    QVector<ClientsInfo*> BlackTeam;
    QVector<ClientsInfo*> WhiteTeam;
    QObject* server;
    QString KingOfLobby;
    LongInt _public_key_e;
    LongInt _public_key_mod;
    LongInt _private_key;
    ClientsInfo* ciKingOfLobby=NULL;
    int numberOfBotBlackTeam=0;
    int numberOfBotWhiteTeam=0;
    bool WhiteKing=0;
    bool Balance=1;
public:
    Lobby(ClientsInfo* ciCreator,QString LobbyName,QObject* server):LobbyName(LobbyName),server(server),
        QObject(0)
    {
        BlackTeam<<ciCreator;
    }
    ~Lobby();
    void SendtoClient(QString,QString);
    void SendtoClients(QString);
    void SendMessagetoClients(QString Text, ClientsInfo *client);
    void addUsers(ClientsInfo* client);
    void addBot(QString);
    void RefreshNumberOfBot(ClientsInfo* client);
    void RefreshNumberOfBot(int& NumberOfBotBlackTeam,int& NumberOfBotWhiteTeam);
    void delUsers(ClientsInfo* client);
    void ChangeTeam(ClientsInfo* client);
    void RefreshList(ClientsInfo* client);
    void newKing();
    bool isKing(QString);
    void StartGame();
    void DeleteLobby();
    //void setPublicKey(LongInt,LongInt);
    void setPrivateKey(LongInt);
    //inline LongInt& public_key_e();
    //inline LongInt& public_key_mod();
    inline LongInt& private_key();
    QVector<ClientsInfo*> take_vectorOfWhiteTeam();
    QVector<ClientsInfo*> take_vectorOfBlackTeam();
    QString lengthOfTeam();
    int lenght();
    QString LobbyName;
    QString pass;

signals:
    void sig_createTheGame();
    void sig_delete();
};

#endif // SERVER_H
