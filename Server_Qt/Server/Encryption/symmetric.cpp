#include "symmetric.h"
Symmetric::Symmetric()
{
}
#define qS QString("symmetric.cpp:")
int Symmetric::_lenght=4;
LongInt Symmetric::_private_key;
void Symmetric::Generation()
{
    _private_key=norm_Random(_lenght,_lenght,false);
    qDebug()<<qS<<"generation private key-"<<_private_key;
}

QString Symmetric::Encryption(const QString& text)
{
    LongInt result;
    QString encryption_text;
    qDebug()<<qS<<"before encryption"<<text;
    qDebug()<<qS<<"lenght:"<<text.length();
    int i;
    for(i=0;i<text.length();i++)
    {
        result.push_back((int)text[i].toLatin1());
        if(_private_key<=result<<1)
        {
            result*=_private_key;
            encryption_text+= result.toString()+(i+1==text.length()?"":"|");
            result.clear();
        }
    }
    if(_private_key>(result<<1))
    {
        result*=_private_key;
        encryption_text+= result.toString();
    }
    qDebug()<<qS<<"after encryption"<<encryption_text;
    return encryption_text;
}

QString Symmetric::Decipherment(const QString& encryption_text)
{
    QStringList qslist=encryption_text.split("|");
    LongInt result;
    qDebug()<<qS<<"before decipherment"<<encryption_text;
    QString dicipherment_text;
    for(int i=0;i<qslist.length();i++)
    {
        result=LongInt(qslist[i]);
        result/=_private_key;
        dicipherment_text+=result.toString()+(i+1==qslist.length()?"":"");
    }
    qDebug()<<qS<<"after decipherment"<<dicipherment_text;
    qslist=dicipherment_text.split(" ");
    dicipherment_text.clear();
    int ch;
    for(int i=0;i<qslist.length();i++)
    {
        ch=qslist[i].toInt();
        if(ch>31)
        {
            while(ch>127)
            {
                ch/=10;
            }
            dicipherment_text+=(char)ch;
        }
        //qDebug()<<qS<<dicipherment_text;
    }
    return dicipherment_text;
}

const LongInt& Symmetric::private_key()
{
    return _private_key;
}

void Symmetric::setPrivateKey(LongInt e)
{
    _private_key=e;
    qDebug()<<qS<<"new private key("<<_private_key<<")";
}

void Symmetric::setLenght(int l)
{
    if(l>=4)
    {
        _lenght=l;
    }
    else
    {
        qDebug()<<qS<<"l<4";
    }
}

inline const LongInt& Symmetric::lenght()
{
    return _lenght;
}
