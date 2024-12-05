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
        void insert(vector<string> &t, Criminal *c);
        void erase(string name, vector<int> &time);
        void searchByTime(vector<int> &time);
        void searchByIntervalTime(vector<int> &time1, vector<int> &time2);
        void searchByTimeCrime(vector<int> &time, string type);
        void searchByIntervalTimeCrime(vector<int> &time1, vector<int> &time2, string type);
        void searchByName(string name);
    public :
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
            Criminal *c;

            if(criminal.find(name) == criminal.end()){
                string id, bir, gen, loc;
                cout << "Input the ID of the Criminal\n";
                cin >> id;
                cout << "Input the birthday of the Criminal\n";
                cin >> bir;
                cout << "Input the gender of the Criminal\n";
                cin >> gen;
                cout << "Input the location of the Criminal\n";
                cin >> loc;
                c = new Criminal(id,bir, gen, loc, name);
                criminal[name] = c;
            }
            string tmp[7]={"crime type (steal, rob, scam, kill, others)","crime description", "year", "month", "day", "hour", "minute"};
            vector<string> t(7, "");
            for(int i=0;i<7;i++){
                cout << "Input the " << tmp[i] << " of the criminal\n";
                cin >> t[i];
            }
            c = criminal[name];
            insert(t, c);
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
            searchByTime(time);
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
            searchByIntervalTime(time1, time2);
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
            searchByTimeCrime(time, type);
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
            searchByIntervalTimeCrime(time1, time2, type);
        }
        else if(choice==7){
            string name;
            cout << "Input the name of the criminal\n";
            cin >> name;
            searchByName(name);
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

void System::insert(vector<string> &t, Criminal *c){
    CrimeRecord *record=new CrimeRecord(t[0],t[1],stoi(t[2]),stoi(t[3]),stoi(t[4]),stoi(t[5]),stoi(t[6]),c);
    c->addcrimeRecord(record);

    int treenum = treeNumber[t[0]];
    crimeTree[treenum].Insert(crimeTree[treenum], record);
}

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

void System::searchByTime(vector<int> &time){
    bool f = false;
    for(int i=0; i<5; i++){
        vector<CrimeRecord*> t = crimeTree[i].SearchTime(time[0],time[1],time[2],time[3],time[4]);
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

void System::searchByIntervalTime(vector<int> &time1, vector<int> &time2){
    bool f = false;
    for(int i=0; i<5; i++){
        vector<CrimeRecord*> t = crimeTree[i].SearchInterval(time1[0],time1[1],time1[2],time1[3],time1[4],time2[0],time2[1],time2[2],time2[3],time2[4]);
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

void System::searchByTimeCrime(vector<int> &time, string type){
    bool f = false;
    vector<CrimeRecord*> t = crimeTree[treeNumber[type]].SearchTime(time[0],time[1],time[2],time[3],time[4]);
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

void System::searchByIntervalTimeCrime(vector<int> &time1, vector<int> &time2, string type){
    bool f = false;
    vector<CrimeRecord*> t = crimeTree[treeNumber[type]].SearchInterval(time1[0],time1[1],time1[2],time1[3],time1[4],time2[0],time2[1],time2[2],time2[3],time2[4]);
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

void System::searchByName(string name){
    if(criminal.find(name) == criminal.end()){
        cout << "The person does not exist\n";
        return;
    }
    Criminal *c = criminal[name];
    c->outputAllinfo();
    c->outputAllRecord();
}

int main(){
    System s;
    s.Main();
}