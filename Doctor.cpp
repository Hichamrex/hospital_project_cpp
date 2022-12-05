#include <iostream>
#include<vector>
#include "Person.h"
#include "Doctor.h"
#include"Patient.h"

using namespace std;
int Doctor::counter=0;
Doctor::Doctor(){ }

Doctor::~Doctor() { }

//(fname,lname,cin,phone,address,speciality,nbPatient,timeWork) add the class patient which is a pointer
Doctor::Doctor(int id_,string fname,string lname,string cin_,string phone_,string address_,string spec_,string time_)
:id(id_),Person(fname,lname,cin_,phone_,address_),speciality(spec_),workTime(time_){
	
}
//getters
string Doctor::getSpeciality(){
	return speciality;
}

int Doctor::getNbPatient(){
	return nbPatient;
}

string Doctor::getWorkTime(){
	return workTime;	
}

int Doctor::getId(){
	return id;
}

//setters
void Doctor::setId(int id_){
	id=id_;
}
void Doctor::setSpeciality(string spec_){
	speciality=spec_;
}

void Doctor::setNbPatient(int nb){
	nbPatient=nb;
}

void Doctor::setWorkTime(string time){
	workTime=time;
}

void Doctor::initialise(istream& input){
	nbPatient=0;
	cout<<"\t|ENTER FIRST NAME: ";
	input>>firstName;
	cout<<"\t|ENTER LAST NAME: ";
	input>>lastName;
	cout<<"\t|ENTER CIN: ";
	input>>cin;
	cout<<"\t|ENTER PHONE NUMBER: ";
	input>>phone;
	cout<<"\t|ENTER ADDRESS: ";
	input.ignore();
	getline(input,address);
	cout<<"\t|ENTER SPECIALITY: ";
	input>>speciality;
	cout<<"\tENTER WORK TIME: ";
	input>>workTime;
	counter++;
	setId(counter);
}

void Doctor::displayed() const{
  
  cout<<"\t\t\t\t\t\t------------------------\n";
  cout<<"\t\t\t\t\t\t|      DOCTOR ID "<<id<<"     |\n";
  cout<<"\t\t\t\t\t\t------------------------\n";	
  cout<<"\t\t--------------------------------------------------------------------------------------------\n";
  cout<<"\t\t|FIRTST NAME: "<<firstName<<" \t\t\t\tLAST NAME: "<<lastName<<"\n";
  cout<<"\t\t|CIN: "<<cin<<"     \t\t\t\tPOHNE: "<<phone<<"\n";
  cout<<"\t\t|SPECIALITY: "<<speciality<<" \t\t\t\tADDRESS: "<<address<<"       \n";
  cout<<"\t\t|NUMBER OF PATIENT: "<<nbPatient<<" \t\t\t\tWORK TIME: "<<workTime<<"\n";
  cout<<"\t\t--------------------------------------------------------------------------------------------\n"; 
}

void Doctor::displayPatients(){
	
	for(int i=0 ; i<nbPatient ; i++){
		listPatient[i].displays();
	}
}

void Doctor::addPatient(Patient& p){
	listPatient[nbPatient]=p;
}

Patient* Doctor::getPatients(){
	return listPatient;
}
