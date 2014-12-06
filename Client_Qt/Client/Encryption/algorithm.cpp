#include "algorithm.h"
//#include "LongNumber/longint.h"
#define qA QString("algorithm.cpp")
LongInt Algorithm::Karatsuba(LongInt a_1, LongInt b_1)
{
    if(a_1.length()==1 || b_1.length()==1)//&&
    {
        return a_1*b_1;
    }

    int length;
    if(a_1.length()!=1 && b_1.length()!=1)
    {
        length=(a_1.length() >= b_1.length() ? b_1.length() : a_1.length() )/2;
        LongInt a_2;
        a_2.number=a_1.getVector_of_Number(a_1.length()-length);
        LongInt b_2;
        b_2.number=b_1.getVector_of_Number(b_1.length()-length);
        LongInt ab_1,ab_2;
        ab_1=Karatsuba(a_1,b_1);
        ab_2=Karatsuba(a_2,b_2);
        return ( (((Karatsuba(a_1+a_2,b_1+b_2)-ab_1-ab_2)<<length)
                  + ab_2)
                 + (ab_1<<(2*length))
               );
    }
}

LongInt Algorithm::Toom_Cook(LongInt a, LongInt b)
{
    /*/
    a=LongInt("529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450");
    b=LongInt("29834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450529834750827340585463450");
    qDebug()<<a.length();
    LongInt z=Strassen(a,b);
    /*/
    //===T1===========initialization=table=and=stack===
    qDebug()<<"Hello Lord of Iteration";
    QStack<LongInt> U,V;
    QStack<LongInt> W;
    QStack<int> C;

    int Index,i,j;//for iteration;
    //=======================Table===========
    int k=1;
    int Q=2,R=1;
    Table table={4,2};

    QVector<Table> qv_table;
    qv_table<<table<<table;
    QVector<Table>::iterator iter_table;//=qv_table.begin();

    int last_q=4;

    qDebug()<<qA<<"\"(0)\""<<Q<<R<<table.q<<table.r;
    while(a.length()>(qv_table.last().q+last_q))
    {
        qDebug()<<"algorithm.cpp:"<<"("+QString::number(k)+")"<<Q<<R<<table.q<<table.r;
        k++;
        Q+=R;
        table.q*=table.r;
        R++;
        if(R*R<=Q)//if((R+1)^2>=Q) R++;
        {
            table.r*=2;
        }
        else R--;
        last_q=qv_table.last().q;
        qv_table<<table;
    }
    qDebug()<<"algorithm.cpp:"<<"("+QString::number(k)+")"<<Q<<R<<table.q<<table.r;
    iter_table=qv_table.end();
    iter_table--;
    LongInt numbers[10*iter_table->r+1];
    //===================T2============================
    C.push(-1);
    C<<a.number<<-5<<b.number;
    a.clear();
    b.clear();
    int forSwitch=1;//iter_table--;
    //====================Cycle========================
    //bool isEnd=0;
    while(1)
    {
        switch(forSwitch)
        {
        case 1://T3
        {
            k--;
            iter_table--;
            //qDebug()<<"K="<<k;
            if(!k)
            {
                a.clear();
                b.clear();
                //qDebug()<<"C="<<C;
                while(!C.isEmpty())
                {
                    Q=C.pop();
                    if(Q>=0)
                    {
                        b.push_front(Q);
                    }
                    else
                    {
                        break;
                    }
                }
                //qDebug()<<"C="<<C;
                while(!C.isEmpty())
                {
                    Q=C.pop();
                    if(Q>=0)
                    {
                        a.push_front(Q);
                    }
                    else
                    {
                        C.push(Q);
                        break;
                    }
                }
                //qDebug()<<"algorithm.cpp:"<<a<<"*"<<b<<"=";
                forSwitch=5;
                a*=b;
                //qDebug()<<"algorithm.cpp:"<<a;
            }
            else
            {
                forSwitch=2;
            }
            break;
        }
        case 2://T4 T5
        {
            //=====T4=========
            Index=0;
            numbers[0].clear();
            //qDebug()<<"T4 C"<<C;

            while(!C.isEmpty())
            {
                Q=C.pop();
                if(Q>=0)
                {
                    if(numbers[Index].length()>=iter_table->q)
                    {
                        //qDebug()<<"algorithm.cpp:("<<Index<<")"<<numbers[Index];
                        numbers[Index].normalization();
                        Index++;
                        numbers[Index].clear();
                    }
                    numbers[Index].push_front(Q);
                }
                else
                {
                    break;
                }
            }
            //qDebug()<<"algorithm.cpp:("<<Index<<")"<<numbers[Index];
            R=iter_table->r+Index;
            //qDebug()<<R;
            //qDebug()<<Index;
            for(j=0;j<=R;j++)
            {
                a=numbers[Index];
                for(i=Index-1;i>=0;i--)
                {
                    a*=j;
                    a+=numbers[i];
                }
                U<<a;
            }
            Index=0;
            numbers[0].clear();
            while(!C.isEmpty())
            {
                Q=C.pop();
                if(Q>=0)
                {
                    if(numbers[Index].length()>=iter_table->q)
                    {
                        //qDebug()<<"algorithm.cpp:("<<Index<<")"<<numbers[Index];
                        numbers[Index].normalization();
                        Index++;
                        numbers[Index].clear();
                    }
                    numbers[Index].push_front(Q);
                }
                else
                {
                    C.push(Q);
                    break;
                }
            }
            //qDebug()<<"algorithm.cpp:("<<Index<<")"<<numbers[Index];
            //qDebug()<<Index;
            for(j=0;j<=R;j++)
            {
                a=numbers[Index];
                //qDebug()<<"algorithm.cpp:j="<<j;
                for(i=Index-1;i>=0;i--)
                {
                    a*=j;
                    a+=numbers[i];
                }
                //qDebug()<<"algorithm.cpp:a="<<a;
                V<<a;
            }
            //qDebug()<<"algorithm.cpp:V="<<V;
            //=====T5=========
            if(!U.isEmpty()||!V.isEmpty())
            {
                C<<-2<<V.pop().number<<-5<<U.pop().number;
                while(!U.isEmpty()||!V.isEmpty())
                {
                    C<<-3<<V.pop().number<<-5<<U.pop().number;
                }
            }
            else
            {
                //qDebug()<<"Error algorithm.cpp: U or V Empty";
            }
            //qDebug()<<"C="<<C;
            b.clear();
            b.push_front(-4);
            W<<b;
            forSwitch=1;
            break;
        }
        case 3://T6
        {
            W<<a;
            forSwitch=1;
            //qDebug()<<"algorithm.cpp:a="<<a;
            break;
        }
        case 4://T7 T8 T9
        {
            //qDebug()<<W<<"\n";
            //W.clear();
            //W<<-4<<10<<304<<1980<<7084<<18526;
            Index=-1;
            while (!W.isEmpty())
            {
                //b=W.pop();
                Index++;
                //qDebug()<<"W="<<W;
                numbers[Index]=W.pop();
                //qDebug()<<W.length();
                if(numbers[Index]<0)
                {
                    //qDebug()<<W.length();
                    Index--;
                    break;
                }
            }
            //qDebug()<<W;
            //=====T7=========
            for(j=1;j<=Index;j++)
            {
                for(i=0;i<=Index-j;i++)
                {
                    numbers[i]=(numbers[i]-numbers[i+1])/LongInt(j);
                    //qDebug()<<"numb"<<numbers[i]<<j;
                }
                //qDebug()<<numbers[Index-j+1]<<j;
            }
            //qDebug()<<numbers[Index-j+1];

            /*/
            for(i=0;i<=Index;i++)
            {
                qDebug()<<"(T7)numbers="<<numbers[i];
            }
            /*/

            //=====T8=========
            //qDebug()<<"";
            for(j=Index-1;j>=1;j--)
            {
                for(i=Index-j;i>=1;i--)
                {
                    //qDebug()<<j<<i;
                    numbers[i]-=numbers[i-1]*j;
                }
            }

            /*/
            for(i=0;i<=Index;i++)
            {
                qDebug()<<"(T8)numbers="<<numbers[i];
            }
            /*/

            //=====T9=========
            a=numbers[0];
            //qDebug()<<iter_table->q;
            for(i=1;i<=Index;i++)
            {
                a=(a<<iter_table->q)+numbers[i];
                //qDebug()<<a<<a.length()<<iter_table->q<<numbers[i];
            }
            //qDebug()<<"";
            forSwitch=5;
            break;
        }
        case 5://T10
        {
            k++;
            iter_table++;
            if(!C.isEmpty())
            switch(C.pop())
            {
            case -1:
            {
                /*/
                qDebug()<<"a=  "<<a;
                qDebug()<<"z=  "<<z;
                if(a==z)
                {
                    qDebug()<<"a=z";
                }
                /*/
                return a;
                break;
            }
            case -2:
            {
                W<<a;
                forSwitch=4;
                //qDebug()<<"-2";
                break;
            }
            case -3:
            {
                forSwitch=3;
                //qDebug()<<"-3";
                break;
            }
            default:
            {
                //qDebug()<<"error";
                break;
            }
            }
            else
            {
                //qDebug()<<"Error algorithm.cpp: C Empty";
            }

            break;
        }
        }
    }
}

//=================Schonhage===============================
LongInt Algorithm::Schonhage(LongInt a, LongInt b)
{
    static QVector<int> prime_numbers;
    static bool isInitialization=0;
    if(!isInitialization)
    {
        prime_numbers.clear();
        prime_numbers<<29<<31<<37<<41<<43<<47<<53<<59<<61<<67<<71<<73<<79<<83<<89<<97<<101;
        isInitialization=1;
        LongInt dob=1;
        for(int i=0;i<prime_numbers.length();i++)
        {
            dob*=prime_numbers[i];
        }
        qDebug()<<dob;
    }

    int i=0,j=0;
    int _c[prime_numbers.length()],c[prime_numbers.length()];
    int part;
    LongInt prime_long_int;
    QVector<int>::iterator iter=prime_numbers.begin();
    //qDebug()<<prime_long_int.length();
    for(;iter<prime_numbers.end();iter++,i++)
    {
        prime_long_int=*iter;
        _c[i]=((a % prime_long_int) * (b % prime_long_int) % prime_long_int).toInt();         //c[i]=a*b mod prime_number[i]
        //qDebug()<<*iter<<_c[i];
    }
    //=============Гаусc=============
    for (i=0; i<prime_numbers.length(); ++i)
    {
        c[i] = _c[i];
        for (j=0; j<i; ++j) {
            c[i] = (c[i] - c[j]) * Modular_Multiplicative_Inverse(prime_numbers[j],prime_numbers[i]);
            part=c[i];
            c[i] = c[i] % prime_numbers[i];
            if (c[i] < 0)  c[i] += prime_numbers[i];
            //qDebug()<<"II:"<<c[i]<<Modular_Multiplicative_Inverse(prime_numbers[j],prime_numbers[i]);
        }
        //qDebug()<<"II:"<<c[i]<<prime_numbers[i];
    }
    a=c[0];
    b=1;
    //qDebug()<<b<<c[0]<<a;
    for(i=1;i<prime_numbers.length();i++)
    {
        b*=prime_numbers[i-1];
        a+=b*c[i];
        qDebug()<<b<<c[i]<<a;
    }
    //==============================
    return a;
}

int Algorithm::Modular_Multiplicative_Inverse(int a,int mod)
{
    if(a>=mod)
    {
        a=a%mod;
    }

    int t;
    int an_2=0,an_1=1;
    int invert;

    int b=a;
        a=mod;

    while(b!=0&&b!=1)
    {
        //qDebug()<<"a b:"<<a<<b;
        //qDebug()<<an_2<<an_1;
        an_2= an_2 - an_1*(a/b);
        invert=an_1;
        an_1=an_2;
        an_2=invert;
        //==========algorithm=HCD(a,b)============
        t=b;
        b=a%b;
        a=t;
        //========================================
    }
    if(b==0)
    {
        qDebug()<<"algorithm.cpp:Modular_Multiplicative_Inverse: HCD(a,mod)="<<a;
        qDebug()<<"Inverse number for a does not exist";
        return a;
    }
    if(an_1<0)
    {
        an_1=mod-an_1;
    }
    return an_1;
}
LongInt Algorithm::Modular_Multiplicative_Inverse(LongInt a, LongInt mod, bool* is_inverse_norm)
{
    //qDebug()<<"algorithm.cpp: Inverse-"<<a<<mod;
    if(a==0)
    {
        qDebug()<<qA<<"Inverse a==0";
        return a;
    }
    if(a<LongInt(0))
    {
        a+=mod;
    }
    if(a>=mod)
    {
        a=a%mod;
    }
    //
    LongInt t;
    LongInt an_2=0,an_1=1;
    LongInt invert;

    LongInt b=a;
        a=mod;

    while(b!=1&&b!=0)
    {
        //qDebug()<<an_2<<an_1;
        //qDebug()<<"a b:"<<a<<b;
        an_2=an_2-an_1*(a/b);
        invert=an_1;
        an_1=an_2;
        an_2=invert;
        //==========algorithm=HCD(a,b)============
        t=b;
        b=a%b;
        a=t;
        //========================================
    }
    if(b==0&&a!=mod&&a!=1)
    {
        qDebug()<<"algorithm.cpp:Modular_Multiplicative_Inverse: HCD(a,mod)="<<a;
        qDebug()<<"Inverse number for a does not exist";
        if(is_inverse_norm!=NULL)
        {
            (*is_inverse_norm)=false;
        }
        return a;
    }
    //
    if(an_1<LongInt(0))
    {
        //qDebug()<<"algorithm.cpp: inverse="<<an_1+mod;
        return mod+an_1;
    }
    if(is_inverse_norm!=NULL)
    {
        (*is_inverse_norm)=true;
    }
    //qDebug()<<"algorithm.cpp: inverse="<<an_1;
    return an_1;
}

//=================Strassen===============================
QDebug  operator <<(QDebug qd,std::complex<double> a)
{
    qd<<"("<<QString::number(a.real())/*+","+QString::number(a.imag())*/<<")";
    return qd;
}
LongInt Algorithm::Strassen (LongInt a, LongInt b)
{
    int n=1;
    while(n<a.length())
    {
        n<<=1;
    }
    n<<=1;
    QVector< std::complex<double> > fa,fb,res(n);
    while(!a.isEmpty())
    {
        fa.push_front(a.number.takeFirst());
    }
    while(!b.isEmpty())
    {
        fb.push_front(b.number.takeFirst());
    }
    while(fa.length()<n)
    {
        fa.push_back(0);
    }
    while(fb.length()<n)
    {
        fb.push_back(0);
    }
    FFT(fa,0);
    FFT(fb,0);
    for(int i=0;i<fa.length();i++)
    {
        fa[i]*=fb[i];
    }
    FFT(fa,1);
    while(!fa.isEmpty())
    {
        a.push_front(fa.takeFirst().real()+0.5);
    }
    a.normalization();

    return a;
}

void Algorithm::FFT(QVector< std::complex<double> > &a, bool invert)
{
    //qDebug()<<a;
    int n=a.length();
    if(n==1)
    {
        return;
    }
    int i;
    QVector< std::complex<double> >a0(n/2),a1(n/2);
    for(i=0;i<n;i+=2)
    {

        a0[i/2]=a[i];
        a1[i/2]=a[i+1];
    }
    FFT(a0,invert);
    FFT(a1,invert);
    static double pi_2;//=M_PI *2;
    double ang=(pi_2/n)*(invert?-1:1);
    std::complex<double> w(1),wn(cos(ang),sin(ang));
    for(i=0;i<n/2;i++)
    {
        a[i]=a0[i]+w*a1[i];
        a[i+ n/2 ]=a0[i]-w*a1[i];
        if(invert)
        {
            a[i]/=2;
            a[i+ n/2 ]/=2;
        }
        w*=wn;

    }
    /*/
    int i,j=0;
    int n=a.length();
    //double pi_2=M_PI *2;
    double ang;
    std::complex<double> w,wn;
    QVector< std::complex<double> > _a(n);
    for(i=0;i<n;i++)
    {
        a_[j]=a[i];
        j=j+n/2;
    }
    n/=2;
    for(;n>1;n/=2)
    {
        ang=(M_PI/n)*(invert?-1:1);
        qDebug()<<"length"<<n;
        w=1,wn={cos(ang),sin(ang)};
        i=0;
        j=0;
        while(1)
        {
            _a[i]=a[i]+w*a[i+n/2];
            _a[i+n]=a[i]-w*a[i+n/2];
            i++,j++;
            if(j==n/2)
            {
                w*=wn;
                j=0;
                i+=n/2;
            }
            qDebug()<<i<<j;
            if(i>=a.length())
            {
                break;
            }
            a=_a;
        }

    }
    /*/
}
//=====================================================

LongInt* Algorithm::Inverse_Number_Toom(LongInt a, LongInt)
{
    //a=LongInt("4712634712341234");
    //qDebug()<<a.length();
    //===========================initialization=============================
    int k=1;
    const int n=a.length()*coef;
    LongDouble* z_double=new LongDouble(1);
    z_double->setSize(-a.length());
    LongInt *z=(LongInt*)z_double;//
    LongInt _z;
    LongInt V_k;
    V_k.number=a.getVector_of_Number(0,3,0);
    *z<<=(n);
    *z/= (V_k);
    //======================================================================
    while(k<n)
    {
        V_k.number=a.getVector_of_Number(0,k*2+3,0);
        //V_k.resize(n);
        _z=V_k*Strassen(*z,*z);
        _z.resize(z->length());
        //qDebug()<<"z*2-_z="<<z*2<<"\n"<<_z;
        *z=*z*2-_z;
        z->resize(n);
        z->normalization();
        k*=2;
    }
    //qDebug()<<*z;
    return z;
}

LongInt* Algorithm::Toom(LongInt a, LongInt b)
{
    LongInt _a=a;
    _a.resize(b.length());
    const int n=a.length()-b.length()+(_a>=b?1:0);
    LongInt* _b=Inverse_Number_Toom(b);
    LongDouble* c=new LongDouble();
    (*c) = ((*_b) * a);
    c->setSize(n);
    qDebug()<<n;
    qDebug()<<c->toString();
    delete _b;
    return (LongInt*)c;
}

//=====================================Primery=test===========================================================

bool Algorithm::Lehmer(LongInt a,int r)
{
    if(!(a.number.last()-(a.number.last()/2)*2))
    {
        return 0;
    }
    LongInt _a,a_j,t=(a-1)/2,j=1;
    for(int i=1;i<=r;i++)
    {
        //============================random===========
        /*/
        _a=LongInt(std::rand());
        _a<<=10;
        _a/=LongInt(RAND_MAX+1);
        _a=(_a % a-2)+2;
        /*/
        _a=Random(2,a-1);
        qDebug()<<"random="<<_a;
        //=============================================
        a_j=Modular_exponentiation(_a,a,t);
        if(a_j == 1 ||a_j == a-1 )
        {
            continue;
        }
        return 0;
    }
   return 1;
}

bool Algorithm::Miller_Rabin(LongInt a, int r)
{
    if(!(a.number.last()-(a.number.last()/2)*2))
    {
        return 0;
    }
    LongInt _a=a-1,a_t,s("0"),t,j;
    int random;
    while(!_a.isEmpty()&&!(_a.number.last()-(_a.number.last()/2)*2))
    {
        _a/=2;
        s+=1;
    }
    t=_a;
    r=s.toInt();
    qDebug()<<t<<s;
    for(int i=1;i<=r;i++)
    {
        //==============random====
        /*/
        _a=LongInt(std::rand())+1;
        _a<<=10;
        _a/=LongInt(RAND_MAX);
        qDebug()<<_a;
        _a=(_a % (a-2))+2;
        /*/
        _a=Random(2,a-1);
        qDebug()<<"random="<<_a;
        a_t=_a;
        //========================
        a_t=Modular_exponentiation(_a,a,t);
        if(a_t==1 || a_t==(a-1))
        {
            qDebug()<<"nextIter";
            continue;
        }
        qDebug()<<"a_t"<<a_t;
        for(j=0;j<s;j+=1)
        {
            a_t=Toom_Cook(a_t,a_t);
            a_t= a_t % a;
            if(a_t==1)
            {
                return 0;
            }
            if(a_t==(a-1))
            {
                goto continue_A;
            }
        }
        return 0;
        continue_A:;
    }
    return 1;
}
bool Algorithm::Solovay_Strassen(LongInt a,int r)
{
    if(!(a.number.last()-(a.number.last()/2)*2))
    {
        return 0;
    }
    LongInt _a,a_j,t=(a-1)/2;
    qDebug()<<t;
    for(int i=1;i<=r;i++)
    {
        //============================random===========
        /*/
        _a=LongInt(std::rand());
        _a<<=10;
        _a/=LongInt(RAND_MAX+1);
        _a=( _a % (a-2))+2;
        /*/
        _a=Random(2,a-1);
        qDebug()<<"random="<<_a;
        a_j=_a;
        //=============================================
        if(HCD(_a,a)>1)
        {
            return 0;
        }
        a_j=Modular_exponentiation(_a,a,t);
        if(a_j== (_a % a) )
        {
            return 0;
        }
    }
    return 1;
}

bool Algorithm::Agrawal_Kayal_Saxena(LongInt a)
{
    LongInt log_2_a=0;
    LongInt _a=a;
    LongInt r(2),k;
    while( _a >=2)
    {
        _a/=2;
        log_2_a += 1;
    }
    //+++++++++++++++1+++++++++++++++
    LongInt a_=a,midle;
    _a=1;
    for(k=2;k <= log_2_a;k+=1)
    {
        _a=0;
        a_=a-1;
        while(1)
        {
            r=(a_+_a)/2;
            midle=(r)^k;
            if(midle==a)
            {
                //qDebug()<<"algorithm.cpp:"<<a<<"="<<r<<"^"<<k;
                return false;
            }
            if(midle>a)  a_=r;
            if(midle<a)  _a=r;
            if((a_-_a)<=1) break;
        }
    }
    //
    //+++++++++++++++2+++++++++++++++
    LongInt sqr_log_2=log_2_a*log_2_a;
    //LongInt maxr=log_2_a^5;
    bool nextR=true;
    for(r=2;nextR/*&&r<maxr*/;r+=1)
    {
        nextR=false;
        _a=1;
        //qDebug()<<"\nr="<<r;
        for(k=1;(!nextR)&&k<=sqr_log_2;k+=1)
        {
            _a=((_a*a) % r);
            //qDebug()<<"algorithm.cpp:Agrawal_Kayal_Saxena"<<k<<_a;
            nextR=(_a==1||_a==0);
        }
    }
    r-=1;
    //qDebug()<<"r="<<r;
    //+++++++++++++++3+++++++++++++++
    for(_a=r;_a>LongInt(1);_a-=1)
    {
        k=HCD(_a,a);
        //qDebug()<<_a;
        if(k==a)
        {
            break;
        }
        if(k>1)
        {
            return false;
        }
    }
    //+++++++++++++++4+++++++++++++++
    if(a<=r)
    {
        return true;
    }
    //
    //+++++++++++++++5+++++++++++++++
    k=2;
    r=LongInt::Sqrt(Eulers_totient(r))*log_2_a;
    //qDebug()<<"Sqrt(Eulers_totient(r))*log_2_a="<<r;
    for(;k<=r;k+=1)
    {
        if(Modular_exponentiation(k,a,a)!=k)
        {
            //qDebug()<<"Modular_exponentiation("<<k<<","<<a<<","<<a<<")=\n"<<Modular_exponentiation(k,a,a);
            return false;
        }

    }
    //+++++++++++++++6+++++++++++++++

    return true;
}

LongInt Algorithm::HCD(LongInt a,LongInt b)
{
    a=+a;b=+b;
    LongInt t;
    while(b!=0)
    {
        //qDebug()<<"algorithm.cpp:HCD (a,b):"<<a<<b;
        t=b;
        b=a%b;
        a=t;
    }
    //qDebug()<<"algorithm.cpp:HCD (a,b) _end"<<a<<b;
    return a;
}

LongInt Algorithm::Modular_exponentiation(LongInt a,LongInt m, LongInt r)
{
    //qDebug()<<"algorithm.cpp: Modular_exponentiation"<<a<<m<<r;
    if(r==0)
    {
        //qDebug()<<"algorithm.cpp: Modular_exponentiation :( 1 )";
        return LongInt(1);
    }
    QVector<LongInt> part;
    part;
    LongInt a_k(1),k(1);

    while(1)
    {
        qDebug()<<a_k<<a<<m;
        a_k=((a_k*a)%m);
        part<<a_k;
        if(part.last()==part.first()&&part.length()!=1)
        {
            qDebug()<<part;
            part.removeLast();
            //qDebug()<<"algorithm.cpp: Modular_exponentiation :"<<part.value( ((r % LongInt(part.length()))).toInt());
            return part.value( ((r % LongInt(part.length()))).toInt());
        }
        k+=1;
        if(k>r)
        {
            //qDebug()<<"algorithm.cpp: Modular_exponentiation :"<<part.value( ((r % LongInt(part.length()))).toInt());
            return part.value( ((r % LongInt(part.length()))).toInt());
            return a_k;
        }
    }
}

LongInt Algorithm::fast_Modular_exponentiation(LongInt a,LongInt r, LongInt m)
{
    LongInt result = 1;
    a = a % m;
    while (r > 0)
    {
        if (r % 2 == 1)
        {
           result = (result * a) % m;
        }
        r= r /2;
        a = a * a % m;
    }
    return result;
}

LongInt Algorithm::Eulers_totient(LongInt n)
{
    LongInt ret(1);
    LongInt i(2);
    LongInt p;
    //LongInt one(1);//
    for(; (i * i) <= n; i+=1)
    {
        p = 1;
        //qDebug()<<LongInt::mod( n , i);
        while(( n % i) == 0)
        {
            p *= i;
            n /= i;
        }
        if((p /= i) >= 1)
        {
            ret *= p * (i - 1);
        }
        //qDebug()<<"ret="<<ret;
    }
    return ( n!=1 ) ? (n-1) * ret : ret;
}

LongInt Algorithm::Random(LongInt inf,LongInt sup)// random є [inf;sup]
{
    if(inf==sup)
    {
        return sup;
    }
    if(inf>sup)
    {
        return -LongInt(0);
    }
    LongInt _a;
    _a=(LongInt(std::rand())%(sup-inf));
    return _a+inf;
}
#define SIZE_OF_RANDOM (4/LongInt::baza_for_initializatio())
#define MAX_OF_NUMERICAL (LongInt::baza()-1)
LongInt Algorithm::norm_Random(LongInt inf, LongInt sup)
{
    if((sup-inf)<MAX_OF_NUMERICAL)
    {
        return Random(inf,sup);
    }
    LongInt result;
    sup=sup-inf;
    LongInt max_i=sup.length()%SIZE_OF_RANDOM,rand;

    max_i=Random(0,sup.length()-1);
    qDebug()<<qA<<"max_i"<<max_i;
    if(max_i==0)
    {
        return inf+Random(0,MAX_OF_NUMERICAL);
    }
    bool is_max=1;
    for(int i=0;max_i>i;i++)
    {
        rand=Random(0,MAX_OF_NUMERICAL);
        if(rand>0)
            is_max=0;
        result=(result<<SIZE_OF_RANDOM)+rand;
    }
    result+= Random(1,sup>>((sup.length()%SIZE_OF_RANDOM))*
                    SIZE_OF_RANDOM+(is_max?0:-1));
    return inf+result;
}

LongInt Algorithm::norm_Random(LongInt inf,LongInt sup,bool is_norm)
{
    if(is_norm)
    {
        if(inf!=sup)
        {
            sup=LongInt(1)<<sup.toInt();
        }
        else
        {
            sup=(LongInt(1)<<(sup.toInt()+1))-1;
        }
        inf=LongInt(1)<<inf.toInt();
        qDebug()<<qA<<inf<<sup;
        return norm_Random(inf,sup);
    }
    else
    {
        if(inf==sup)
        {
            inf=LongInt(1)<<inf.toInt();
            sup=(LongInt(1)<<(sup.toInt()+1))-1;
            LongInt result;
            sup=sup-inf;
            LongInt max_i=sup.length()%SIZE_OF_RANDOM,rand;

            max_i=sup.length()-1;//Random(0,sup.length()-1);
            //qDebug()<<qA<<"max_i"<<max_i;
            if(max_i==0)
            {
                return inf+Random(0,MAX_OF_NUMERICAL);
            }
            bool is_max=1;
            for(int i=0;max_i>i;i++)
            {
                rand=Random(0,MAX_OF_NUMERICAL);
                if(rand>0)
                    is_max=0;
                result=(result<<SIZE_OF_RANDOM)+rand;
            }
            result+= Random(1,sup>>((sup.length()%SIZE_OF_RANDOM))*
                            SIZE_OF_RANDOM+(is_max?0:-1));
            return inf+result;
        }
        else
            return norm_Random(inf,sup);
    }
}

//============================================================================================================

LongInt Algorithm::HelloWorldofTest(LongInt a, LongInt b)
{
    return Lehmer(11);//Algorithm::Random(-LongInt(1),1);
    LongInt max(1);
    max.resize(6);
    for(LongInt i(10);i<max;i+=1)
    {
        if(Agrawal_Kayal_Saxena(i))
        {
            qDebug()<<i<<"-prime";
        }
    }
    return a;//LongInt::Sqrt_n(a,3);
}
