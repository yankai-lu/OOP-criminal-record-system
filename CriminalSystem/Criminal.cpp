#include<iostream>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem
{
    Criminal::Criminal():head(nullptr),tail(nullptr) {}
    Criminal::Criminal(string i,string bir,string g,string loca,string n,string type,string description,int y,int month,int day,int hour,int minute):Person(i,bir,g,loca,n)
    {
        CrimeRecord *c=new CrimeRecord(type,description,y,month,day,hour,minute,c,c);
        head=c;
        tail=c;
    }
    const CrimeRecord* Criminal::getHead()
    {
        return head;
    }
    const CrimeRecord* Criminal::getTail()
    {
        return tail;
    }
    void Criminal::addcrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,CrimeRecord)
    {
        CrimeRecord *c=new CrimeRecord(t,d,y,month,day,hour,minute);

        if(head==tail)
        {
            head=c;
            tail=c;
            c->setNext(c);
            c->setPrev(c);
        }
        else
        {
            tail->setNext(c);
            c->setPrev(tail);
            c->setNext(head);
            head->setPrev(c);
            tail=c;
        }
    }

    void Criminal::outputAllinfo()
    {
        cout << *this << endl ;
    }
    Criminal* seachCrimeRecord(int y,int month,int day,int hour,int minute)
    {
        
    }
}