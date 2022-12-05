#include <iostream>
#include<string>

#include "Person.h"
#include "Patient.h"

using namespace std;

int Patient::counter=0;

Patient::Patient(){ }

Patient::~Patient(){ }


Patient::Patient(string fname,string lname,string cin_,string phone_,string address_,string disease_,string nameDoctor_,string sleep_,int
  numR_,int nbDays)
  :Person(fname,lname,cin_,phone_,address_),disease(disease_),nameDoctor(nameDoctor_),sleep(sleep_),numRoom(numR_),nbOfDays(nbDays){
	
}

//Getters
string Patient::getDisease(){
	return disease;
}

string Patient::getNameDoctor(){
	return nameDoctor;
}

int Patient::getNumRoom(){
	return numRoom;	
}

int Patient::getNbOfDays(){
	return nbOfDays;
}

string Patient::getSleep(){
	return sleep;
}

int Patient::getidDoctor(){
	return idDoctor;
}
//Setters
void Patient::setDisease(string dis){
	disease=dis;
}

void Patient::setSleep(string sleep_){
	sleep=sleep_;
}

void Patient::setNbOfDays(int nb){
	nbOfDays=nb;
}

void Patient::setNumRoom(int nb){
	numRoom=nb;
}

void Patient::setNameDoctor(string name){
	nameDoctor=name;
}

void Patient::readPatient(istream& input){

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
	cout<<"\t|ENTER DISEASE: ";
	input>>disease;
	cout<<"\t|ENTER IF THE PATIENT WILL SLEEP INTO THE HOPITAL<yes,no>: ";
	input>>sleep;
	if(sleep=="yes"){
		cout<<"\tENTER THE ROOM NUMBER : ";
		input>>numRoom;
		cout<<"\tENTER THE NUMBER OF THE DAYS HE/SHE WILL BE INSIDE THE HOPTIAL: ";
		input>>nbOfDays;
	}
	counter++;
}

void Patient::displays() const{
	 cout<<"\t\t\t\t\t\t--------------------\n";
  	 cout<<"\t\t\t\t\t\t|     PATIENT      |\n";
     cout<<"\t\t\t\t\t\t--------------------\n";	
     cout<<"\t\t--------------------------------------------------------------------------------------------\n";
     cout<<"\t\t|FIRTST NAME: "<<firstName<<" \t\t\t\tLAST NAME: "<<lastName<<"\n";
     cout<<"\t\t|CIN: "<<cin<<"     \t\t\t\tPOHNE: "<<phone<<"\n";
     cout<<"\t\t|DISEASE: "<<disease<<" \t\t\tADDRESS: "<<address<<       "\n";
     cout<<"\t\t|ID OF DOCTOR: "<<idDoctor<<" \t\t\t\tNAME OF THE DOCTOR: "<<nameDoctor<<"\n";
     cout<<"\t\t|SLEEPING INSIDE THE HOPITAL: "<<sleep<<" \t\t\t\t\n";
    if(sleep=="yes"){
		cout<<"\t\t|ROOM NUMBER: "<<numRoom<<" \t\t\t\tNUMBER OF DAYS: "<<nbOfDays<<endl;
	}
     cout<<"\t\t--------------------------------------------------------------------------------------------\n"; 
}

void Patient::setIdDoctor(int id){
	idDoctor=id;
}

