#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "CriminalSystem.h"
#include "RBTree_criminalRecord.cpp"

using namespace std;
using namespace CriminalSystem;

class System{
    private :
        RB_Tree crimeTree[5];
        map<string, int> treeNumber;
        map<string, Criminal*> criminal;
    public :
        void insert(string criminalType, string description, int year, int month, int day, int hour, int minute, string id, string bir, string gen, string loc, string name);
        void erase(string name, vector<int> &time);
        void searchByTime(int year, int month, int day, int hour, int minute);
        void searchByIntervalTime(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2);
        void searchByTimeCrime(int year, int month, int day, int hour, int minute, string type);
        void searchByIntervalTimeCrime(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2, string type);
        int searchByName(string name, char** array, int row, int col);
        
        System();
        void Main();
};

System::System(){
    string tmp[5]={"steal","rob" ,"scam" ,"kill" ,"others"};
    for(int i=0;i<5;i++){
        treeNumber[tmp[i]] = i;
    }
}


void System::Main(){
    int choice = 0;
    do{
        if(choice==1){
            string name;
            cout << "Input the name of the Criminal\n";
            cin >> name;

            string id, bir, gen, loc;
            if(criminal.find(name) == criminal.end()){
                cout << "Input the ID of the Criminal\n";
                cin >> id;
                cout << "Input the birthday of the Criminal\n";
                cin >> bir;
                cout << "Input the gender of the Criminal\n";
                cin >> gen;
                cout << "Input the location of the Criminal\n";
                cin >> loc;
            }
            else
            {
                id = criminal[name]->getId();
                bir = criminal[name]->getBirthday();
                gen = criminal[name]->getGender();
                loc = criminal[name]->getLocation();
            }
            string tmp[7]={"crime type (steal, rob, scam, kill, others)","crime description", "year", "month", "day", "hour", "minute"};
            vector<string> t(7, "");
            for(int i=0;i<7;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> t[i];
            }
            insert(t[0], t[1], stoi(t[2]), stoi(t[3]), stoi(t[4]), stoi(t[5]), stoi(t[6]), id, bir, gen, loc, name);
        }
        else if(choice==2){
            string name;
            vector<int> time(5, 0);
            cout << "Input the name of the Criminal\n";
            cin >> name;
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> time[i];
            }
            erase(name, time);
        }
        else if(choice==3){
            vector<int> time(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> time[i];
            }
            searchByTime(time[0], time[1], time[2], time[3], time[4]);
        }
        else if(choice==4){
            vector<int> time1(5, 0), time2(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "1 of the criminal\n";
                cin >> time1[i];
            }
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "2 of the criminal\n";
                cin >> time2[i];
            }
            searchByIntervalTime(time1[0], time1[1], time1[2], time1[3], time1[4], time2[0], time2[1], time2[2], time2[3], time2[4]);
        }
        else if(choice==5){
            string type;
            cout << "Input the type of the crime\n";
            cin >> type;
            vector<int> time(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> time[i];
            }
            searchByTimeCrime(time[0], time[1], time[2], time[3], time[4], type);
        }
        else if(choice==6){
            string type;
            cout << "Input the type of the crime\n";
            cin >> type;
            vector<int> time1(5, 0), time2(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "1 of the criminal\n";
                cin >> time1[i];
            }
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "2 of the criminal\n";
                cin >> time2[i];
            }
            searchByIntervalTimeCrime(time1[0], time1[1], time1[2], time1[3], time1[4], time2[0], time2[1], time2[2], time2[3], time2[4], type);
        }
        else if(choice==7){
            string name;
            cout << "Input the name of the criminal\n";
            cin >> name;
            searchByName(name, NULL, 0, 0);
        }
        else if(choice!=0){
            cout << "Wrong input\n";
        }
        cout << "\n";
        cout << "Choice\n";
        cout << "0. End the System\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search by time\n";
        cout << "4. Search by interval of time\n";
        cout << "5. Search by time and type of crime\n";
        cout << "6. Search by interval of time and type of crime\n";
        cout << "7. Search by criminal's name\n";
    }
    while(cin >> choice && choice);

    cout << "System Stop\n";
}


/*
void System::Main(){
    int choice = 0;
    do{
        if(choice==1){
            string name;
            cout << "Input the name of the Criminal\n";
            cin >> name;
            cin.ignore();

            string id, bir, gen, loc;
            if(criminal.find(name) == criminal.end()){
                cout << "Input the ID of the Criminal\n";
                getline(cin, id);
                cout << "Input the birthday of the Criminal\n";
                getline(cin, bir);
                cout << "Input the gender of the Criminal\n";
                getline(cin, gen);
                cout << "Input the location of the Criminal\n";
                getline(cin, loc);
            }
            else
            {
                id = criminal[name]->getId();
                bir = criminal[name]->getBirthday();
                gen = criminal[name]->getGender();
                loc = criminal[name]->getLocation();
            }
            string tmp[7]={"crime type (steal, rob, scam, kill, others)","crime description", "year", "month", "day", "hour", "minute"};
            vector<string> t(7, "");
            for(int i=0;i<7;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                getline(cin, t[i]);
            }
            insert(t[0], t[1], stoi(t[2]), stoi(t[3]), stoi(t[4]), stoi(t[5]), stoi(t[6]), id, bir, gen, loc, name);
        }
        else if(choice==2){
            string name;
            vector<int> time(5, 0);
            cout << "Input the name of the Criminal\n";
            cin >> name;
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> time[i];
            }
            erase(name, time);
        }
        else if(choice==3){
            vector<int> time(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> time[i];
            }
            searchByTime(time[0], time[1], time[2], time[3], time[4]);
        }
        else if(choice==4){
            vector<int> time1(5, 0), time2(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "1 of the criminal\n";
                cin >> time1[i];
            }
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "2 of the criminal\n";
                cin >> time2[i];
            }
            searchByIntervalTime(time1[0], time1[1], time1[2], time1[3], time1[4], time2[0], time2[1], time2[2], time2[3], time2[4]);
        }
        else if(choice==5){
            string type;
            cout << "Input the type of the crime\n";
            cin >> type;
            vector<int> time(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> time[i];
            }
            searchByTimeCrime(time[0], time[1], time[2], time[3], time[4], type);
        }
        else if(choice==6){
            string type;
            cout << "Input the type of the crime\n";
            cin >> type;
            vector<int> time1(5, 0), time2(5, 0);
            string tmp[5]={"year", "month", "day", "hour", "minute"};
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "1 of the criminal\n";
                cin >> time1[i];
            }
            for(int i=0;i<5;i++){
                cout << "Input the " << tmp[i] << "2 of the criminal\n";
                cin >> time2[i];
            }
            searchByIntervalTimeCrime(time1[0], time1[1], time1[2], time1[3], time1[4], time2[0], time2[1], time2[2], time2[3], time2[4], type);
        }
        else if(choice==7){
            string name;
            cout << "Input the name of the criminal\n";
            cin >> name;
            searchByName(name, NULL, 0, 0);
        }
        else if(choice!=0){
            cout << "Wrong input\n";
        }
        cout << "\n";
        cout << "Choice\n";
        cout << "0. End the System\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search by time\n";
        cout << "4. Search by interval of time\n";
        cout << "5. Search by time and type of crime\n";
        cout << "6. Search by interval of time and type of crime\n";
        cout << "7. Search by criminal's name\n";
    }
    while(cin >> choice && choice);

    cout << "System Stop\n";
}
*/
//  新增犯罪紀錄
void System::insert(string criminalType, string description, int year, int month, int day, int hour, int minute, string id, string bir, string gen, string loc, string name){
    Criminal* c;    //  罪犯檔案

    //  判斷這個人有沒有前科
    if(criminal.find(name) == criminal.end()){
        // 沒有前科，新增一個罪犯檔案
        c = new Criminal(id, bir, gen, loc, name);
        criminal[name] = c;
    }
    else{
        //  有前科，引用之前的檔案
        c = criminal[name];
    }
    
    CrimeRecord *record=new CrimeRecord(criminalType, description, year, month, day, hour, minute, c);
    c->addcrimeRecord(record);

    int treenum = treeNumber[criminalType];
    crimeTree[treenum].Insert(crimeTree[treenum], record);
}



//  刪除犯罪紀錄
void System::erase(string name, vector<int> &time){
    if(criminal.find(name) == criminal.end()){
        cout << "The person does not exist\n";
        return;
    }
    Criminal *c = criminal[name];
    CrimeRecord *record = c->getRecord_time(time);
    if(record==NULL){
        cout << "Record does not exist in the System\n";
    }
    else{
        int treeNum = treeNumber[record->getType()];
        c->deletecrimeRecord(record);
        crimeTree[treeNum].Delete(crimeTree[treeNum], record);
    }
}

//  搜尋某個特定時間點的犯罪紀錄
void System::searchByTime(int year, int month, int day, int hour, int minute){
    bool f = false;
    for(int i=0; i<5; i++){
        vector<CrimeRecord*> t = crimeTree[i].SearchTime(year, month, day, hour, minute);
        for(int i=0;i<t.size();i++){
            f=true;
            cout << "-------------------------------------\n";
            t[i]->getCriminal()->outputAllinfo();
            cout << *t[i];
            cout << "-------------------------------------\n";
        }
    }
    if(!f){
        cout << "No crime on that time\n";
    }
}

//  搜尋某個時間區間的犯罪紀錄
void System::searchByIntervalTime(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2){
    bool f = false;
    for(int i=0; i<5; i++){
        vector<CrimeRecord*> t = crimeTree[i].SearchInterval(year1, month1, day1, hour1, minute1, year2, month2, day2, hour2, minute2);
        for(int i=0;i<t.size();i++){
            f = true;
            cout << "-------------------------------------\n";
            t[i]->getCriminal()->outputAllinfo();
            cout << *t[i];
            cout << "-------------------------------------\n";
        }
    }
    if(!f){
        cout << "No crime on that time\n";
    }
}

//  搜尋某個特定時間點的特定形式犯罪紀錄
void System::searchByTimeCrime(int year, int month, int day, int hour, int minute, string type){
    bool f = false;
    vector<CrimeRecord*> t = crimeTree[treeNumber[type]].SearchTime(year, month, day, hour, minute);
    for(int i=0;i<t.size();i++){
        f = true;
        cout << "-------------------------------------\n";
        t[i]->getCriminal()->outputAllinfo();
        cout << *t[i];
        cout << "-------------------------------------\n";
    }
    
    if(!f){
        cout << "No crime on that time\n";
    }
}

//  搜尋某個時間區間的特定形式犯罪紀錄
void System::searchByIntervalTimeCrime(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2, string type){
    bool f = false;
    vector<CrimeRecord*> t = crimeTree[treeNumber[type]].SearchInterval(year1, month1, day1, hour1, minute1, year2, month2, day2, hour2, minute2);
    for(int i=0;i<t.size();i++){
        f = true;
        cout << "-------------------------------------\n";
        t[i]->getCriminal()->outputAllinfo();
        cout << *t[i];
        cout << "-------------------------------------\n";
    }
    if(!f){
        cout << "No crime on that time\n";
    }
}

//  搜尋某個人的所有犯罪紀錄
int System::searchByName(string name, char** array, int row, int col) {
    if(criminal.find(name) == criminal.end()){
        cout << "The person does not exist\n";
        return -1;
    }
    Criminal *c = criminal[name];
    c->outputAllinfo();
    c->outputAllRecord(array, row, col);

    return c->getNumOfRecord();
}


//  The system
System s;


/*
    ====================================================
    ============== 以下為C++和Python的連接 ==============
    ====================================================
*/

extern "C" {
    __declspec(dllexport) void newCriminal(char* criminalType, char* description, int year, int month, int day, int hour, int minute, char* id, char* bir, char* gen, char* loc, char* name){
        string type(criminalType);
        string des(description);
        string idString(id);
        string birString(bir);
        string genString(gen);
        string locString(loc);
        string nameString(name);
        s.insert(type, des, year, month, day, hour, minute, id, bir, gen, loc, name);
    }
} 

extern "C" {
    __declspec(dllexport) void deleteCriminal(char* name, int year, int month, int day, int hour, int minute){
        vector<int> time(5, 0);
        time[0] = year;
        time[1] = month;
        time[2] = day;
        time[3] = hour;
        time[4] = minute;
        string nameString(name);
        s.erase(name, time);
    }
}

extern "C" {
    __declspec(dllexport) void searchbyTime(int year, int month, int day, int hour, int minute){
        s.searchByTime(year, month, day, hour, minute);
    }
}

extern "C"{
    __declspec(dllexport) void searchbyIntervalTime(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2){
        s.searchByIntervalTime(year1, month1, day1, hour1, minute1, year2, month2, day2, hour2, minute2);
    }
}

extern "C"{
    __declspec(dllexport) void searchbyTimeCrime(int year, int month, int day, int hour, int minute, char* type){
        s.searchByTimeCrime(year, month, day, hour, minute, type);
    }
}

extern "C"{
    __declspec(dllexport) void searchbyIntervalTimeCrime(int year1, int month1, int day1, int hour1, int minute1, int year2, int month2, int day2, int hour2, int minute2, char* type){
        s.searchByIntervalTimeCrime(year1, month1, day1, hour1, minute1, year2, month2, day2, hour2, minute2, type);
    }
}

extern "C"{
    __declspec(dllexport) int searchbyName(char* name, char** array, int row, int col){
        return s.searchByName(name, array, row, col);
    }
}

//  test
extern "C"{
    __declspec(dllexport) int main(){
        s.Main();
    }
}