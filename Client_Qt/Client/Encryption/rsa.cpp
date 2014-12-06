#include "rsa.h"
#define qR QString("rsa.cpp:")

LongInt RSA::_min_key=LongInt(1)<<6;
LongInt RSA::p_1(17);//("162259276829213363391578010288127");
LongInt RSA::p_2(19);//("170141183460469231731687303715884105727");
LongInt RSA::_public_key_mod=RSA::p_1*RSA::p_2;
LongInt RSA::_public_key_e;
LongInt RSA::_private_key_d;

RSA::RSA()
{
}
void RSA::Generation()
{
    const static LongInt e_f=(p_1-1)*(p_2-1);
    bool* is_norm_inverse=new bool;
    _public_key_e=norm_Random(2,e_f-1);
    _private_key_d=Modular_Multiplicative_Inverse(public_key_e(),e_f,is_norm_inverse);
    while(!*is_norm_inverse)
    {
        _public_key_e=norm_Random(2,e_f-1);
        _private_key_d=Modular_Multiplicative_Inverse(public_key_e(),e_f,is_norm_inverse);
        if(_public_key_e==_private_key_d)
        {
            *is_norm_inverse=0;
            continue;
        }
    }
    delete is_norm_inverse;
    qDebug()<<qR<<"new public key=("<<public_key_mod()<<","<<public_key_e()<<")";
    qDebug()<<qR<<"new private key="<<private_key_d();
    qDebug()<<qR<<"test: public*private"<<(_public_key_e*_private_key_d)%public_key_mod();
}

const LongInt& RSA::public_key_mod()
{
    return _public_key_mod;
}

const LongInt& RSA::public_key_e()
{
    return _public_key_e;
}

const LongInt& RSA::private_key_d()
{
    return _private_key_d;
}
/*/
void RSA::setMinLenght(int lenght)
{
    qDebug()<<qR<<"new min lenght-"<<lenght;
    _min_key= LongInt(1)<<lenght;
}
/*/
QString RSA::Encryption(const QString& text)
{
    LongInt result;
    QString encryption_text;
    qDebug()<<qR<<"before encryption"<<text;
    qDebug()<<qR<<"lenght:"<<text.length();
    ;int i;
    for(i=0;i<text.length();i++)
    {
        result.push_back((int)text[i].toLatin1());
        if(_public_key_e<=result<<1)
        {
            //qDebug()<<qR<<result;
            result=fast_Modular_exponentiation(result,_public_key_e,_public_key_mod);
            encryption_text+= result.toString()+(i+1==text.length()?"":"|");
            result.clear();
        }
    }
    if(_public_key_e>result<<1)
    {
        result=fast_Modular_exponentiation(result,_public_key_e,_public_key_mod);
        encryption_text+= result.toString();
    }
    qDebug()<<qR<<"after encryption"<<encryption_text;
    //qDebug()<<qR<<"lenght-"<<lenght;
    return encryption_text;
}

QString RSA::Decipherment(const QString& encryption_text)
{
    QStringList qslist=encryption_text.split("|");
    LongInt result;
    qDebug()<<qR<<"before decipherment"<<encryption_text;
    QString dicipherment_text;
    for(int i=0;i<qslist.length();i++)
    {
        result=LongInt(qslist[i]);
        result=fast_Modular_exponentiation(result,_private_key_d,_public_key_mod);
        dicipherment_text+=result.toString()+(i+1==qslist.length()?"":"");
    }
    qDebug()<<qR<<"after decipherment"<<dicipherment_text;
    qslist=dicipherment_text.split(" ");
    dicipherment_text.clear();
    for(int i=0;i<qslist.length();i++)
    {
        dicipherment_text+=(char)qslist[i].toInt();
        qDebug()<<dicipherment_text;
    }
    return dicipherment_text;
}
