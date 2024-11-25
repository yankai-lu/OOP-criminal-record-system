#include<iostream>
#include"CriminalSystem.h"
using namespace std;

namespace CriminalSystem
{
    Person::Person() {}
    Person::Person(string i,string bir,string g,string loca,string n):id(i),birthday(bir),gender(g),location(loca),name(n) {}
    const string Person::getId()
    {
        return id;
    }
    void Person::setId(string i)
    {
        id=i;
    }
    const string Person::getBirthday()
    {
        return birthday;
    }
    void Person::setBirthday(string b)
    {
        birthday=b;
    }
    const string Person::getGender()
    {
        return gender;
    }
    void Person::setGender(string g)
    {
        gender=g;
    }
    const string Person::getLocation()
    {
        return location;
    }
    void Person::setLocation(string loca)
    {
        location=loca;
    }
    const string Person::getName()
    {
        return name;
    }
    void Person::setName(string n)
    {
        name=n;
    }
    ostream& operator <<(ostream& out,Person& p)
    {
        out << "Name : " << p.name << endl ;
        cout << "Gender : " << p.gender << endl ;
        out << "Birthday : " << p.birthday << endl ;
        out << "Id : " << p.id << endl ;
        out << "Address : " << p.location  ;

        return out;
    }
}