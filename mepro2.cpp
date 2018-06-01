#include<iostream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<fstream>
using namespace std;
class createacc
{
    int pass;
    public:
        long long int no;
        string nm;
        char act;
        int tp,ctp;
        float rs;
        void name()
        {cout<<"\n*Enter your name: ";cin.ignore();getline(cin,nm);}
        void mob()
        {cout<<"*Enter your mob.no.: ";cin>>no;}
        void actype()
        {cout<<"1. Saving\t2. Current\nyou must write only first char.\n";cout<<"*Enter your Account type: ";cin>>act;}
        void pwd()
        {cout<<"*Enter your 4 digit password: ";cin>>pass;while((pass>9999)||(pass<1000)){cout<<"Please re-enter your password. = ";cin>>pass;}}
        void rpi()
        {cout<<"How many Rs. You want to deposit.\n(minimum diposit Rs. 1000): ";cin>>rs;while(rs<1000){cout<<"Min. amount deposit Rs. 1000.00 : ";cin>>rs;}}
        void acid()
        {static long long int id=70707500;tp=id;ctp=id;++id;}
        void file()
        {
            cout<<"Your Account No. is -> "<<ctp;
            char fname[13];
            itoa(ctp,fname,10);
            strcat(fname,".txt");
            ofstream fout,fch;
            fout.open(fname,ios::out);
            fout<<"% Name              : "<<nm<<"\n";
            fout<<"% Mob.no.           : "<<no<<"\n";
            fout<<"% Account Type & NO.: "<<act;
            fout<<ctp<<"\n";
            fout<<"% Total Rs. is      :% "<<rs;
            fout.close();
            fch.open("checking.txt");
            fch<<tp;
            fch.close();
        }
};
class login:protected createacc
{
    int y;
    long int cno;
    public:
        int checkno(long long int z)
        {
            cno=z;
            if(z<tp)
            {y=0;}
            else
            {y=1;}
            return y;
        }
        void shwdat(long long int z)
        {
            int x;
            x=checkno(z);
            if(x==1)
            {
                char fnm[13],c;
                itoa(cno,fnm,10);
                ifstream getd;
                strcat(fnm,".txt");
                getd.open(fnm,ios::in);
                c=getd.get();
                while(!getd.eof())
                {if((int)c==37){}else{cout<<c;}c=getd.get();}
                getd.close();
            }
            else
            {cout<<"Account does not exist.\n";}
        }
};
class cashtran:protected login
{
    long int acn;
    public:
        void cashdep()
        {
            int k;
            cout<<"Enter your Acc. no.: ";
            cin>>acn;
            cin.ignore();
            k=checkno(acn);
            char of[13],dof[500],c;
            itoa(acn,of,10);
            strcat(of,".txt");
            if(k==1)
            {
                cout<<"\n\t\tHow many Rs. = ";
                cin>>k;
                ifstream fin;
                fin.open(of,ios::in);
                int i=0,j=0,e;
                unsigned char r[20];
                c=fin.get();
                while(!fin.eof())
                {
                    if((int)c==37)
                    {j++;}
                    if(j==5)
                    {
                        if(i>=11)
                        {i=0;}
                        if((int)c>=48 && (int)c<=57)
                        {r[i]=c;i++;}
                    }
                    if(j!=5)
                    {dof[i]=c;e=i;}
                    i++;
                    c=fin.get();
                }
                fin.close();
                cin.ignore();
                float w=0,y;
                int u=1;
                for(i=20;i>=0;i--)
                {
                    if((int)r[i]>=48 && (int)r[i]<=57)
                    {y=(float)(r[i]-'0');y=y*u;w=w+y;u=u*10;}
                }
                w=w+k;
                j=0;
                i=0;
                ofstream fout;
                fout.open(of,ios::out);
                while(i!=(e+1))
                {fout<<dof[i];i++;}
                fout<<"% "<<w;
                fout.close();
                cout<<"Total Rs. in your acc. : "<<w;
            }
            else
            {cout<<"Account does not exist.\n";}
        }
        void cashwid()
        {
            int k;
            cout<<"Enter your Acc. no.: ";
            cin>>acn;
            cin.ignore();
            k=checkno(acn);
            char of[13],dof[500],c;
            itoa(acn,of,10);
            strcat(of,".txt");
            if(k==1)
            {
                cout<<"\n\t\tHow many Rs. = ";
                cin>>k;
                ifstream fin;
                fin.open(of,ios::in);
                int i=0,j=0,e;
                unsigned char r[20];
                c=fin.get();
                while(!fin.eof())
                {
                    if((int)c==37)
                    {j++;}
                    if(j==5)
                    {
                        if(i>=11)
                        {i=0;}
                        if((int)c>=48 && (int)c<=57)
                        {r[i]=c;i++;}
                    }
                    if(j!=5)
                    {dof[i]=c;e=i;}
                    i++;
                    c=fin.get();
                }
                fin.close();
                cin.ignore();
                float w=0,y;
                int u=1;
                for(i=20;i>=0;i--)
                {
                    if((int)r[i]>=48 && (int)r[i]<=57)
                    {y=(float)(r[i]-'0');y=y*u;w=w+y;u=u*10;}
                }
                if(w>k)
                {
                    w=w-k;
                    j=0;
                    i=0;
                    ofstream fout;
                    fout.open(of,ios::out);
                    while(i!=(e+1))
                    {fout<<dof[i];i++;}
                    fout<<"% "<<w;
                    fout.close();
                    cout<<"Total Rs. in your Acc. : "<<w;
                }
                else
                {cout<<"\nyou don't have enough money.\n";}
            }
            else
            {cout<<"Account does not exist.\n";}
        }
};
int main(void)
{
    cout<<"\t|| Bank Of ZER0 ||\n";
    while(1)
    {
        cout<<"\n1. Create your account.";
        cout<<"\n2. Check Account Detail.";
        cout<<"\n3. Cash Deposit or Withdraw.";
        cout<<"\n4. exit.\n";
        cout<<"Enter your choice. = ";
        char b;
        cin>>b;
        switch(b)
        {
            case '1':
            {
                static int i=0;
                createacc ci;
                ci.name();
                ci.mob();
                ci.actype();
                ci.pwd();
                ci.acid();
                ci.rpi();
                ci.file();
                i++;
                break;
            }
            case '2':
            {
                cout<<"Check Acc. details\n";
                login l;
                int x;
                cout<<"Enter your Acc. No. = ";
                cin>>x;
                l.shwdat(x);
                break;
            }
            case '3':
            {
                cout<<"\n^^^1. Cash Deposit.\n^^^2. Cash Withdrawl\n";
                int x;
                cin>>x;
                cashtran c;
                if(x==1)
                {
                    c.cashdep();
                }
                else if(x==2)
                {
                    c.cashwid();
                }
                else
                {cout<<"\nYour Input is invalid.\n";}
                break;
            }
            case '4':{return 0;}
            default:
                cout<<"Your Input is invalid.";
        }
    }
}
