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
    void Criminal::outputAllinfo(char** array, int row, int col, int& index){
        cout << *this << endl ;
        cout << "Number of Records :" << numOfRecord << endl;

        if(array == NULL)
            return;
        
        //  Copy the information of the criminal to the 2D array
        if(index + 5 > row){
            //  index out of bound
            cout << "The 2D array is not enough\n";
            exit(EXIT_FAILURE);
        }

        //  first line in block
        strcpy(array[index], this->getName().c_str()); index++;
        strcpy(array[index], this->getId().c_str()); index++;
        strcpy(array[index], this->getGender().c_str()); index++;
        strcpy(array[index], this->getBirthday().c_str()); index++;

        //  second line in block
        strcpy(array[index], this->getLocation().c_str()); index++;
    }
    void Criminal::outputAllRecord(char** array, int row, int col){
        for(int i=0;i<numOfRecord;i++)
        {
            cout << "-------------------------------------\n";
            cout << *records[i] << endl ;
            cout << "-------------------------------------\n";
        }

        if(array == NULL)
            return;
        
        int index = 0;  // row in 2D array
        
        //  Copy the information of the criminal to the 2D array
        for(int i = 0; i < this->numOfRecord; i++){
            //  detection
            if(index + 8 > row){
                //  index out of bound
                cout << "The 2D array is not enough\n";
                exit(EXIT_FAILURE);
            }

            //  first line in block
            strcpy(array[index], this->getName().c_str()); index++;
            strcpy(array[index], this->getId().c_str()); index++;
            strcpy(array[index], this->getGender().c_str()); index++;
            strcpy(array[index], this->getBirthday().c_str()); index++;

            //  second line in block
            strcpy(array[index], this->getLocation().c_str()); index++;
            strcpy(array[index], this->records[i]->getType().c_str()); index++;
            strcpy(array[index], this->records[i]->getTime_str().c_str()); index++;
            strcpy(array[index], this->records[i]->getDescription().c_str()); index++;
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

    int Criminal::getNumOfRecord() const{
        return numOfRecord;
    }
}