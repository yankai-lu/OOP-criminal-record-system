#ifndef CRIMINALSYSTEM_H
#define CRIMINALSYSTEM_H

#include<iostream>
#include<vector>
#include<map>
using namespace std;

namespace CriminalSystem{
    class Criminal;
    class RB_Tree;
    
    class CrimeRecord{
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
            CrimeRecord(int c,CrimeRecord* l,CrimeRecord* r,CrimeRecord* parent);
            CrimeRecord(string t,string d,int y,int month,int day,int hour,int minute,Criminal* crimi,int c=0,CrimeRecord *l=nullptr,CrimeRecord *r=nullptr,CrimeRecord *parent=nullptr);
            string getType() const;
            void setType(string t);
            vector<int> getRealTime() const;
            int getTime() const;
            void setTime(int y,int month,int day,int hour,int minute);
            string getDescription() const;
            void setDescription(string d);
            CrimeRecord* getLeft() const;
            void setLeft(CrimeRecord* other);
            CrimeRecord* getRight() const;
            void setRight(CrimeRecord* other);
            CrimeRecord* getParent() const;
            void setParent(CrimeRecord* other);
            int getColor() const;
            void setColor(int c);
            Criminal* getCriminal() const;
            void setCriminal(Criminal* other);
            friend ostream& operator <<(ostream& out,const CrimeRecord& cr);
    };
    typedef CrimeRecord Node;
    class Person{
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

    class Criminal : public Person{
        private:
            int numOfRecord;
            vector<CrimeRecord*> records;
        public:
            Criminal();
            Criminal(string i,string bir,string g,string loca,string n);
            ~Criminal();
            void addcrimeRecord(CrimeRecord* record);
            //void deletecrimeRecord(CrimeRecord* record);
            void outputAllinfo();
            void outputAllRecord();
            bool DeleteCrimeRecord(map<string,int>& treeNumber,RB_Tree* crimeTree, vector<int>& t);
            void DeleteAllCrimeRecord(map<string,int>& treeNumber,RB_Tree* crimeTree);
            //CrimeRecord* getRecord_time(vector<int> t);
    };

    class RB_Tree{
            Node* root;
            Node* nil;
            void _leftRotate(RB_Tree& T, Node* x);
            void _rightRotate(RB_Tree& T, Node* x);
            void Transplant(RB_Tree& T, Node* z, Node* y);
            void InsertFixup(RB_Tree& T, Node* x);
            void DeleteFixup(RB_Tree& T, Node* x);
            Node* TreeMinimum(Node* r);
            void display(int* months);
            vector<Node*> Interval(Node* node, int time1, int time2);
        public:
            RB_Tree(void){
                nil = new Node(1,nil,nil,nil);
                root = nil;
            }
            void Insert(RB_Tree& T, Node* z);
            void Delete(RB_Tree& T, Node* z);
            vector<Node*> SearchTime(int year, int month, int day, int hour, int minute);
            vector<Node*> SearchInterval(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2);
    };
}
#endif
