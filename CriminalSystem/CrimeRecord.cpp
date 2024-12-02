#include<iostream>
#include<vector>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem{    
    void display(int* months){
        for(int i=2;i<=12;i++)
            months[i]+=months[i-1];
    }
    CrimeRecord::CrimeRecord():left(nullptr),right(nullptr),p(nullptr) {}
    CrimeRecord::CrimeRecord(int c,CrimeRecord* l,CrimeRecord* r,CrimeRecord* parent):color(c),left(l),right(r),p(p) {}
    CrimeRecord::CrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,Criminal* crimi,int c,CrimeRecord *l,CrimeRecord *r,CrimeRecord *parent):type(t),description(d),left(l),right(r),p(parent),color(c),criminal(crimi){
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        time=y*525600+(months[month-1]+day)*1440+hour*60+minute;
        //cout << time << endl ;
    }
    string CrimeRecord::getType() const{
        return type;
    }
    void CrimeRecord::setType(string t){
        type=t;
    }
    vector<int> CrimeRecord::getRealTime() const{
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        
        vector<int> res;
        int temp=time;
        int year=temp/525600;
        res.push_back(year);
        temp%=525600;
        
        int days=temp/1440;
        temp%=1440;
        int month=1;
        while(months[month]<days)
            month++;
        res.push_back(month);

        int day=days-months[month-1];
        res.push_back(day);
        
        int hour=temp/60;
        res.push_back(hour);
        int minute=temp%=60;
        res.push_back(minute);

        return res;
    }
    int CrimeRecord::getTime() const{
        return time;
    }
    void CrimeRecord::setTime(int y,int month,int day,int hour,int minute){
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        time=y*525600+(months[month-1]+day)*1440+hour*60+minute;
    }
    CrimeRecord* CrimeRecord::getLeft() const{
        return left;
    }
    void CrimeRecord::setLeft(CrimeRecord* other){
        left=other;
    }
    CrimeRecord* CrimeRecord::getRight() const{
        return right;
    }
    void CrimeRecord::setRight(CrimeRecord* other){
        right=other;
    }
    CrimeRecord* CrimeRecord::getParent() const{
        return p;
    }
    void CrimeRecord::setParent(CrimeRecord* other){
        p=other;
    }
    int CrimeRecord::getColor() const{
        return color;
    }
    void CrimeRecord::setColor(int c){
        color=c;
    }
    Criminal* CrimeRecord::getCriminal() const{
        return criminal;
    }
    void CrimeRecord::setCriminal(Criminal* other){
        criminal=other;
    }
    ostream& operator <<(ostream& out,const CrimeRecord& cr){
        int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        display(months);
        
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
        out << "Crime description : " << cr.description << endl;

        return out;
    }   
}