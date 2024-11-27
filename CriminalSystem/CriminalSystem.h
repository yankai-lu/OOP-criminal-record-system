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
            string getType() const;
            void setType(string t);
            vector<int> getTime() const;
            void setTime(int y,int month,int day,int hour,int minute);
            string getDescription() const;
            void setDescription(string d);
            CrimeRecord* getLeft() const;
            void setLeft(CrimeRecord* other);
            CrimeRecord* getRight() const;
            void setRight(CrimeRecord* other);
            CrimeRecord* getParent() const;
            void setParent(CrimeRecord* other);
            Criminal* getCriminal() const;
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
        string getId() const;
        void setId(string i);
        string getBirthday() const;
        void setBirthday(string b);
        string getGender() const;
        void setGender(string g);
        string getLocation() const;
        void setLocation(string loca);
        string getName() const;
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

