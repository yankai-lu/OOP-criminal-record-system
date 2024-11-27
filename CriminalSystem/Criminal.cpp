#include<iostream>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem
{
    Criminal::Criminal():numOfRecord(0) {}
    Criminal::Criminal(string i,string bir,string g,string loca,string n):Person(i,bir,g,loca,n),numOfRecord(0) {}  
    void Criminal::addcrimeRecord(CrimeRecord* record)
    {
        records.push_back(record);
        numOfRecord++;
    }
    void Criminal::outputAllinfo()
    {
        cout << *this << endl ;
    }
    void Criminal::outputAllRecord()
    {
        for(int i=0;i<numOfRecord;i++)
        {
            cout << "-------------------------------------\n" ;
            cout << *records[i] << endl ;
            cout << "-------------------------------------\n" ;
            cout << endl ;
        }
    }
}
