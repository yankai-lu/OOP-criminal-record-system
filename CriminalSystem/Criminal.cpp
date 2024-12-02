#include<iostream>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem{
    Criminal::Criminal():numOfRecord(0) {}
    Criminal::Criminal(string i,string bir,string g,string loca,string n):Person(i,bir,g,loca,n),numOfRecord(0) {}  
    void Criminal::addcrimeRecord(CrimeRecord* record){
        records.push_back(record);
        numOfRecord++;
    }
    void Criminal::deletecrimeRecord(CrimeRecord* record){
        for(int i=0;i<records.size();i++){
            if(records[i]==record){
                records.erase(records.begin()+i);
                numOfRecord--;
                return;
            }
        }
        return;
    }
    void Criminal::outputAllinfo(){
        cout << *this << endl ;
        cout << "Number of Records :" << numOfRecord << endl;
    }
    void Criminal::outputAllRecord(){
        for(int i=0;i<numOfRecord;i++)
        {
            cout << "-------------------------------------\n";
            cout << *records[i] << endl ;
            cout << "-------------------------------------\n";
        }
    }
    CrimeRecord* Criminal::getRecord_time(vector<int> t){
        for(int i=0;i<records.size();i++){
            vector<int> tmp = records[i]->getRealTime();
            if(tmp==t){
                return records[i];
            }
        }
        return NULL;
    }
}