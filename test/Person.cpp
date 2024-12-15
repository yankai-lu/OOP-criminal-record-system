#include <iostream>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem{
    Person::Person() {}
    Person::Person(string i,string bir,string g,string loca,string n):id(i),birthday(bir),gender(g),location(loca),name(n) {}
    string Person::getId() const{
        return id;
    }
    void Person::setId(string i){
        id=i;
    }
    string Person::getBirthday() const{
        return birthday;
    }
    void Person::setBirthday(string b){
        birthday=b;
    }
    string Person::getGender() const{
        return gender;
    }
    void Person::setGender(string g){
        gender=g;
    }
    string Person::getLocation() const{
        return location;
    }
    void Person::setLocation(string loca){
        location=loca;
    }
    string Person::getName() const{
        return name;
    }
    void Person::setName(string n){
        name=n;
    }
    ostream& operator <<(ostream& out,Person& p){
        out << "Name : " << p.name << endl;
        out << "Gender : " << p.gender << endl;
        out << "Birthday : " << p.birthday << endl;
        out << "Id : " << p.id << endl;
        out << "Address : " << p.location;
        return out;
    }
}