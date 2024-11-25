#include<iostream>
#include<vector>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem
{
    
    void display(int* months)
    {
        for(int i=2;i<=12;i++)
            months[i]+=months[i-1];
    }
    CrimeRecord::CrimeRecord():next(nullptr),prev(nullptr) {}
    CrimeRecord::CrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,CrimeRecord* n,CrimeRecord* p):type(t),description(d),next(n),prev(p)
    {
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        time=y*525600+(months[month-1]+day)*1440+hour*60+minute;
        //cout << time << endl ;
    }
    const string CrimeRecord::getType()
    {
        return type;
    }
    void CrimeRecord::setType(string t)
    {
        type=t;
    }
    const int CrimeRecord::getTime()
    {
        
        
    }
    void CrimeRecord::setTime(int y,int month,int day,int hour,int minute)
    {
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        time=y*525600+(months[month-1]+day)*1440+hour*60+minute;
    }
    const CrimeRecord* CrimeRecord::getNext()
    {
        return next;
    }
    void CrimeRecord::setNext(CrimeRecord* other)
    {
        next=other;
    }
    const CrimeRecord* CrimeRecord::getPrev()
    {
        return prev;
    }
    void CrimeRecord::setPrev(CrimeRecord* other)
    {
        prev=other;
    }
    ostream& operator <<(ostream& out,const CrimeRecord& cr)
    {
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        for(int i=0;i<13;i++)
        {
            cout << months[i] << " " ;
        }
        cout << endl ;
        
        int temp=cr.time;
        int year=temp/525600;
        temp%=525600;
        
        int days=temp/1440;
        temp%=1440;
        int month=1;
        while(months[month]<days)
            month++;
        int day=days-months[month-1];
        
        int hour=temp/60;
        int minute=temp%=60;

        out << "Time : " << year << "/" << month << "/" << day << " " << hour << ":" << minute << endl ;
        out << "Crime type : " << cr.type << endl ;
        out << "Crime description : " << cr.description << endl ;

        return out;
    }
    
}