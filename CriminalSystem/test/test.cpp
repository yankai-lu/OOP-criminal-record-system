#include<iostream>
#include"CriminalSystem.h"
using namespace std;
using namespace CriminalSystem;

int main()
{
    
    Criminal c("H12344","2000/5/9","Male","good downtown ok_street","David");
    CrimeRecord *record=new CrimeRecord("kill","Kill a person",2024,11,3,13,30,&c);
    c.addcrimeRecord(record);
    c.outputAllinfo();
    c.outputAllRecord();

    //cout << *(c.getHead()) << endl ;

    return 0;
}
