#include <iostream>
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
        void search();
        void insert();
        void erase();
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
            insert();
        }
        else if(choice==2){
            erase();
        }
        else if(choice==3){
            search();
        }
        else if(choice!=0){
            cout << "Wrong input\n";
        }
        cout << "Choice\n";
        cout << "0. End the System\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
    }
    while(cin >> choice && choice);

    cout << "System Stop\n";
}

void System::search(){
    int choice;
    string t[5] = {"time only", "interval of time only", "time and type of crime", "interval of time and type of record", "criminal's name"};
    for(int i=0; i<5; i++){
        cout << i+1 << " Based on " << t[i] << endl;
    }
    cin >> choice;
    if(choice == 1){
        vector<int> time;
        string tmp[5]={"year", "month", "day", "hour", "minute"};
        for(int i=0;i<5;i++){
            cout << "Input the " << tmp[i] << " of the criminal\n";
            int t;
            cin >> t;
            time.push_back(t);
        }
        bool f=false;
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
    else if(choice == 2){
        vector<int> time1,time2;
        string tmp[5]={"year", "month", "day", "hour", "minute"};
        for(int i=0;i<5;i++){
            cout << "Input the " << tmp[i] << "1 of the criminal\n";
            int t;
            cin >> t;
            time1.push_back(t);
        }
        for(int i=0;i<5;i++){
            cout << "Input the " << tmp[i] << "2 of the criminal\n";
            int t;
            cin >> t;
            time2.push_back(t);
        }
        bool f=false;
        for(int i=0; i<5; i++){
            vector<CrimeRecord*> t = crimeTree[i].SearchInterval(time1[0],time1[1],time1[2],time1[3],time1[4],time2[0],time2[1],time2[2],time2[3],time2[4]);
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
    else if(choice == 3){
        string type;
        cout << "Input the type of the crime\n";
        cin >> type;
        vector<int> time;
        string tmp[5]={"year", "month", "day", "hour", "minute"};
        for(int i=0;i<5;i++){
            cout << "Input the " << tmp[i] << " of the criminal\n";
            int t;
            cin >> t;
            time.push_back(t);
        }
        bool f=false;
        
        vector<CrimeRecord*> t = crimeTree[treeNumber[type]].SearchTime(time[0],time[1],time[2],time[3],time[4]);
        for(int i=0;i<t.size();i++){
            f=true;
            cout << "-------------------------------------\n";
            t[i]->getCriminal()->outputAllinfo();
            cout << *t[i];
            cout << "-------------------------------------\n";
        }
        
        if(!f){
            cout << "No crime on that time\n";
        }
    }
    else if(choice == 4){
        string type;
        cout << "Input the type of the crime\n";
        cin >> type;
        vector<int> time1,time2;
        string tmp[5]={"year", "month", "day", "hour", "minute"};
        for(int i=0;i<5;i++){
            cout << "Input the " << tmp[i] << "1 of the criminal\n";
            int t;
            cin >> t;
            time1.push_back(t);
        }
        for(int i=0;i<5;i++){
            cout << "Input the " << tmp[i] << "2 of the criminal\n";
            int t;
            cin >> t;
            time2.push_back(t);
        }
        bool f=false;
        vector<CrimeRecord*> t = crimeTree[treeNumber[type]].SearchInterval(time1[0],time1[1],time1[2],time1[3],time1[4],time2[0],time2[1],time2[2],time2[3],time2[4]);
        for(int i=0;i<t.size();i++){
            f=true;
            cout << "-------------------------------------\n";
            t[i]->getCriminal()->outputAllinfo();
            cout << *t[i];
            cout << "-------------------------------------\n";
        }
        if(!f){
            cout << "No crime on that time\n";
        }
    }
    else if(choice == 5){
        string name;
        cout << "Input the name of the criminal\n";
        cin >> name;
        if(criminal.find(name) == criminal.end()){
            cout << "The person does not exist\n";
            return;
        }
        Criminal *c = criminal[name];
        c->outputAllinfo();
        c->outputAllRecord();
    }
    else{
        cout << "Wrong input\n";
    }
}
void System::insert(){
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
    string t[7];
    for(int i=0;i<7;i++){
        cout << "Input the " << tmp[i] << " of the criminal\n";
        cin >> t[i];
    }
    c = criminal[name];
    CrimeRecord *record=new CrimeRecord(t[0],t[1],stoi(t[2]),stoi(t[3]),stoi(t[4]),stoi(t[5]),stoi(t[6]),c);
    c->addcrimeRecord(record);

    int treenum = treeNumber[t[0]];
    crimeTree[treenum].Insert(crimeTree[treenum], record);
}
void System::erase(){
    string name;
    vector<int> time;
    cout << "Input the name of the Criminal\n";
    cin >> name;
    string tmp[5]={"year", "month", "day", "hour", "minute"};
    for(int i=0;i<5;i++){
        cout << "Input the " << tmp[i] << " of the criminal\n";
        int t;
        cin >> t;
        time.push_back(t);
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

// int main(){
//     System s;
//     s.Main();
// }