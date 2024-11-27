#ifndef CRIMINALSYSTEM_H
#define CRIMINALSYSTEM_H

#include<iostream>
#include<vector>
using namespace std;

namespace CriminalSystem
{
    class Criminal;
    class CrimeRecord
        {
        private:
            string type;
            int time;
            string description;
            CrimeRecord *left;
            CrimeRecord *right;
            CrimeRecord *p;
            int color;
            Criminal *criminal;
        public:
            CrimeRecord();
            CrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,int c,Criminal* crimi,CrimeRecord *l=nullptr,CrimeRecord *r=nullptr,CrimeRecord *parent=nullptr);
            const string getType();
            void setType(string t);
            const vector<int> getTime();
            void setTime(int y,int month,int day,int hour,int minute);
            const string getDescription();
            void setDescription(string d);
            const CrimeRecord* getLeft();
            void setLeft(CrimeRecord* other);
            const CrimeRecord* getRight();
            void setRight(CrimeRecord* other);
            const CrimeRecord* getParent();
            void setParent(CrimeRecord* other);
            const Criminal* getCriminal();
            void setCriminal(Criminal* other);
            friend ostream& operator <<(ostream& out,const CrimeRecord& cr);
        };

    class Person
    {
    private:
        string id;
        string birthday;
        string gender;
        string location;
        string name;
    public:
        Person();
        Person(string i,string bir,string g,string loca,string n);
        const string getId();
        void setId(string i);
        const string getBirthday();
        void setBirthday(string b);
        const string getGender();
        void setGender(string g);
        const string getLocation();
        void setLocation(string loca);
        const string getName();
        void setName(string n);
        friend ostream& operator <<(ostream& out,Person& p);
    };

    class Criminal : public Person
    {
    private:
        int numOfRecord;
        vector<CrimeRecord*> records;
    public:
        Criminal();
        Criminal(string i,string bir,string g,string loca,string n,string type,string description,int y,int month,int day,int hour,int minute,int num=1);
        //void addcrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,CrimeRecord);
        void outputAllinfo();
        void outputAllRecord();

    };
}
#endif

