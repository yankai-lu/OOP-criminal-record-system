#ifndef CRIMINALSYSTEM_H
#define CRIMINALSYSTEM_H

#include<iostream>
using namespace std;

namespace CriminalSystem
{
    class CrimeRecord
        {
        private:
            string type;
            int time;
            string description;
            CrimeRecord *next;
            CrimeRecord *prev;
        public:
            CrimeRecord();
            CrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,CrimeRecord *n=nullptr,CrimeRecord *p=nullptr);
            const string getType();
            void setType(string t);
            const int getTime();
            void setTime(int y,int month,int day,int hour,int minute);
            const string getDescription();
            void setDescription(string d);
            const CrimeRecord* getNext();
            void setNext(CrimeRecord* other);
            const CrimeRecord* getPrev();
            void setPrev(CrimeRecord* other);
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
        CrimeRecord *head;
        CrimeRecord *tail;
    public:
        Criminal();
        Criminal(string i,string bir,string g,string loca,string n,string type,string description,int y,int month,int day,int hour,int minute);
        const CrimeRecord* getHead();
        const CrimeRecord* getTail();
        void addcrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,CrimeRecord);
        Criminal* seachCrimeRecord(int y,int month,int day,int hour,int minute);
        void outputAllinfo();
        void outputAllRecord();

    };
}
#endif

