#ifndef DOCTOR_H
#define DOCTOR_H
#include<vector>
#include "Patient.h"

class Doctor : public Person{
	
	private:
		int id;
	    std::string speciality;
	    int nbPatient;
	    Patient listPatient[10];
	    std::string workTime;
	public:
		static int counter;
		Doctor();
		~Doctor();

		Doctor(int,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
		void displayed() const; 
		void displayPatients() const; 
		friend istream& operator >>(istream&,Doctor&);
		void initialise(istream&);
		int getNbPatient(); 
		std::string getSpeciality();  
		std::string getWorkTime();
		void setSpeciality(std::string); 
		void setNbPatient(int);
		void setWorkTime(std::string);
		int getId();
		void setId(int); 
		void displayPatients(); 
		void addPatient(Patient&);
		Patient* getPatients();
};

#endif
