#include <iostream>
#include <cstring>
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
    void Criminal::outputAllRecord(char** array, int row, int col){
        //cout << "test: " << this->records[0]->getDescription() << '\n';
        for(int i=0;i<numOfRecord;i++)
        {
            cout << "-------------------------------------\n";
            cout << *records[i] << endl ;
            cout << "-------------------------------------\n";
        }

        int index = 0;  // row in 2D array
        
        /*
        //  Copy the information of the criminal to the 2D array
        for(int i = 0; i < this->numOfRecord; i++){
            //  first line in block
            strcpy(array[index], this->getName().c_str()); index++;
            strcpy(array[index], this->getId().c_str()); index++;
            strcpy(array[index], this->getGender().c_str()); index++;
            strcpy(array[index], this->getBirthday().c_str()); index++;

            //  second line in block
            strcpy(array[index], this->records[i]->getType().c_str()); index++;
            strcpy(array[index], this->records[i]->getTime_str().c_str()); index++;
            strcpy(array[index], this->getLocation().c_str()); index++;
            strcpy(array[index], this->records[i]->getDescription().c_str()); index++;
        }
        */
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

    int Criminal::getNumOfRecord() const{
        return numOfRecord;
    }
}