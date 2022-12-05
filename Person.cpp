#include<iostream>
#include<istream>
#include<string>
#include "Person.h"

using namespace std;

Person::Person() { }

Person::~Person(){ }

Person::Person(string fname,string lname,string cin_,string phone_,string address_)
  :firstName(fname),lastName(lname),cin(cin_),phone(phone_),address(address_){
  	
}
//Getters
string Person::getFname(){
	return firstName;
}

string Person::getLname(){
	return lastName;
}

string Person::getCin(){
	return cin;
}

string Person::getPhone(){
	return phone;
}

string Person::getAddress(){
	return address;
}
//Setters for modifying the data membre in the class
void Person::setFname(string fname){
	firstName=fname;
}

void Person::setLname(string lname){
	lastName=lname;
}

void Person::setCin(string cin_){
	cin=cin_;
}

void Person::setPhone(string phone_){
	phone=phone_;
}

void Person::setAddress(string ad){
	address=ad;
}



