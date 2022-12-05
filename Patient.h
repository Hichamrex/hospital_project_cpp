#ifndef PATIENT_H
#define PATIENT_H

class Patient: public Person{
	private:
	  std::string disease; 
	  std::string nameDoctor; 		
	  std::string sleep; 
	  int numRoom;
	  int nbOfDays; 
	  int idDoctor;
	public:
		static int counter;
		Patient();
		~Patient();
		Patient(std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,int,int);
		std::string getDisease(); 
		std::string getNameDoctor();
		std::string getSleep();
		int getNumRoom(); 
		int getNbOfDays();
		void setDisease(std::string);
		void setNameDoctor(std::string);
		void setSleep(std::string);
		void setNumRoom(int);
		void setNbOfDays(int);
		int getidDoctor();
		void setIdDoctor(int);
		void readPatient(istream&);
		friend istream& operator >>(istream&,Patient&);
		void displays() const;
};

#endif
