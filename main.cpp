#include <iostream>
#include<stdlib.h>
#include<vector>
#include "Person.h"
#include "Doctor.h"
#include "Patient.h"
#include "Manager.h"

using namespace std;
//prototype of some functions 
void homeMenu(vector<Doctor>&,vector<Patient>&,Manager&);


//To read the data from Doctor class
istream& operator >>(istream& input,Doctor& d){
	d.initialise(input);
	return input;
}
//To read the data from Patient class
istream& operator >>(istream& input,Patient& p){
	p.readPatient(input);
	return input;
}
//This function can search for a doctor who can help this patient and add this patient to the list of Patient inside the doctor object
int searchToPutNameDoctor(Patient& pat,vector<Doctor>& doc){
	bool find=false;
	for(int i=0 ; i<Doctor::counter ; ++i){
		if(pat.getDisease()==doc[i].getSpeciality()){
			pat.setNameDoctor(doc[i].getFname());
			pat.setIdDoctor(doc[i].getId());
			doc[i].addPatient(pat);
			doc[i].setNbPatient(doc[i].getNbPatient()+1);
			find=true;
			return 1;
		}
	}
	return -1;
}

//Add multiple doctors at the same time if you want
void addDoctor(int nb,vector<Doctor>& d){
	int from=Doctor::counter;
	int end=Doctor::counter+nb;
	for(int i=from ; i<end ; i++){
		cout<<"\t|-------ENTER THE INFORMATION ABOUT THE <"<<i+1<<"> DOCTOR-------\n";
		cin>>d[i];
	}
}

//To display a doctor by his ID
void displayDoctorID(int id_,vector<Doctor>& d){
	if(Doctor::counter>0){
		if(Doctor::counter>=id_ && id_>0){
			d[id_-1].displayed();
		}else if(id_<=0){
			cout<<"\t--------------------------------------------------------------------\n";
			cout<<"\t|              OPS ! you typed a negative ID                       |\n";
			cout<<"\t--------------------------------------------------------------------\n";
		}else{
			cout<<"\t----------------------------------------------------------------------------------\n";
			cout<<"\t| OPS ! you typed an ID bigger than we have which means the DOCTOR doesn't exist |\n";
			cout<<"\t----------------------------------------------------------------------------------\n";
		}
	}else{
		cout<<"\t--------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no DOCTOR  |\n";
		cout<<"\t--------------------------------------------------------------------\n";
	}
	
}
//Change the ids of doctors after delete one doctor
void changeIds(vector<Doctor>& d){
	int ids=1;
	for(int i=0 ; i<Doctor::counter ; i++){
		d[i].setId(ids++);
	}
}

//This function it helps us to find the doctor who has the same speciality then we need to affect all the patients into this doctor
//the first thing we need to search for a doctor which has the same specialilty
int searchDoctorSameSpeciality(string spec,int id,vector<Doctor>& d){
	for(int i=0 ; i<Doctor::counter ; i++){
		if(i!=id-1 && spec==d[i].getSpeciality()){
		   return i;
		}
	}
	return -1;
}

//To change the ids o f all patient that are under the doctor 
void changeIdsPatient(Doctor& d){
	if(d.getNbPatient()>0){
		Patient *patient=d.getPatients();
		for(int i=0 ; i<d.getNbPatient() ; i++){
			patient[i].setIdDoctor(d.getId());
		}
	}

}

//To change the Ids of the current Patients when delete a doctor
void changeIdsCurPatient(vector<Patient>& p){
	for(int i=0 ; i<Patient::counter ; i++){
		p[i].setIdDoctor(p[i].getidDoctor()-1);
	}
}

//Put all the patients to another doctor who has the same speciality when we delete a doctor
void putPatient(Doctor& del,Doctor& put,vector<Patient>& p,vector<Doctor>& d){
	int from,end;
	from=put.getNbPatient();
	end=from+del.getNbPatient();
	Patient *delPat=del.getPatients();
	
	for(int i=0 ; i<del.getNbPatient() ; i++){
		if(p[i].getidDoctor()==del.getId()){
			p[i].setIdDoctor(put.getId());
			p[i].setNameDoctor(put.getFname());
		}
	}
	Patient *putPat=put.getPatients();
	for(int j=0,i=from ; i<end ; i++,j++){
		put.addPatient(delPat[j]);
		put.setNbPatient(put.getNbPatient()+1);
		putPat[i].setIdDoctor(put.getId());
		putPat[i].setNameDoctor(put.getFname());
	}
}
/*Nif we delete the doctor we need to assign all the patients into another doctor who has the same speciality with this doctor 
if there is no doctor has the same speciality we cant delete the doctor*/
void deleteDoctor(int id,vector<Doctor>& d,vector<Patient>& pat){
	if(Doctor::counter>0){
		int found=searchDoctorSameSpeciality(d[id-1].getSpeciality(),id,d);
		
		if(found!=-1 || d[id-1].getNbPatient()==0){
			if(d[id-1].getNbPatient()>0)
				putPatient(d[id-1],d[found],pat,d);
			for(int i=id-1 ; i<Doctor::counter-1 ; i++){
				d[i]=d[i+1];
			}
			//change the IDs of the rest of patients
			changeIds(d);
			Doctor::counter--;
			for(int i=0 ; i<Doctor::counter ; i++)
				changeIdsPatient(d[i]);	
		    changeIdsCurPatient(pat);	
		    cout<<"\t-------------------------------------------\n";
			cout<<"\t| Congratulations ! The doctor is deleted |\n";
			cout<<"\t-------------------------------------------\n";	
		}else{
			cout<<"\t--------------------------------------------------------------------------------------------------\n";
			cout<<"\t| OPS ! You can't delete this DOCTOR because there's no one who has the same speciality with him |\n";
			cout<<"\t--------------------------------------------------------------------------------------------------\n";	
		}
	}else{
		cout<<"\t--------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no DOCTOR  |\n";
		cout<<"\t--------------------------------------------------------------------\n";
	}	
}
 
//Add patient into the table of patients
void addPatients(int nbPatient,vector<Patient>& p,vector<Doctor>& d){
	int end,from=Patient::counter;
	end=Patient::counter+nbPatient;
	for(int i=from ; i<end ; i++){
		cout<<"\t|-------ENTER THE INFORMATION ABOUT THE <"<<i+1<<"> PATIENT-------\n";
		cin>>p[i];
			
		if(searchToPutNameDoctor(p[i],d)==-1){
			cout<<"\t---------------------------------------------------------------------------------------------\n";
			cout<<"\t| OPS ! There is no DOCTOR with this speciality you can take the patient to another HOSPITAL |\n";
			cout<<"\t---------------------------------------------------------------------------------------------\n";
			Patient::counter--;
			i--;
			end--;
		}
	}
}

//Display a doctor by CIN
void displayDoctorCin(vector<Doctor>& d,string cin){
	if(Doctor::counter>0){
		bool find=false;
	   for(int i=0 ; i<Doctor::counter ; i++){
			if(d[i].getCin()==cin){
				d[i].displayed();
				find=true;
				break;
			}
		}
		if(!find){
			cout<<"\t--------------------------------------------------------------------\n";
			cout<<"\t|           OPS ! There is no DOCTOR with this CIN                 |\n";
			cout<<"\t--------------------------------------------------------------------\n";
		}		
	}else{
		cout<<"\t--------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no DOCTOR  |\n";
		cout<<"\t--------------------------------------------------------------------\n";
	}
	
	
}

//display all the doctors
void displayAllDoctors(vector<Doctor>& d){
	if(Doctor::counter>0){
		for(int i=0 ; i<Doctor::counter ; i++)
			d[i].displayed();
	}else{
		cout<<"\t-------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no DOCTOR |\n";
		cout<<"\t-------------------------------------------------------------------\n";
	}

}

//Display all the Patients
void displayPatients(vector<Patient>& p){
	if(Patient::counter>0){
		for(int i=0 ; i<Patient::counter ; i++){
			p[i].displays();
		}	
	}else{
		cout<<"\t--------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no PATIENT |\n";
		cout<<"\t--------------------------------------------------------------------\n";
	}
	
}
//Search for a patient by CIN
int searchPatient(vector<Patient>& p,string cin){
	if(Patient::counter>0){
		for(int i=0 ; i<Patient::counter ; i++)
		if(p[i].getCin()==cin)
			return i;
	}else{
		cout<<"\t--------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no PATIENT |\n";
		cout<<"\t--------------------------------------------------------------------\n";
	}
	  return -1;		
}
//Display the patient by his/her CIN
void displayPatientCin(vector<Patient>& pat,string cin){
	int index;
	index=searchPatient(pat,cin);
	if(index!=-1)
		pat[index].displays();
	else if(Patient::counter!=0){
		cout<<"\t---------------------------------------\n";
		cout<<"\t|  OPS ! There's no PATIENT with CIN  |\n";
		cout<<"\t---------------------------------------\n";
	}	
}

//Display information about the doctor who's helping this patient
void displayinfoDoctor(vector<Patient>& p,string cni,vector<Doctor>& d){
	int index;
	index=searchPatient(p,cni);
	if( index!=-1 )
		d[index].displayed();
	else if(Patient::counter!=0 && index==-1){
		cout<<"\t---------------------------------------\n";
		cout<<"\t| OPS ! There's no PATIENT with CIN   |\n";
		cout<<"\t---------------------------------------\n";
	}
}
//Delete the patient inside the list of patient in the doctor
void delPatientfrList(int index,vector<Doctor>& d,string cin){
	int nb;
	Patient *list;
 
	 list=d[index-1].getPatients();
	 nb=d[index-1].getNbPatient();
		for(int i=0 ; i<nb ; i++){
			if(list[i].getCin()==cin){
				for(int j=i ; j<nb-1 ; j++){
					list[j]=list[j+1];
				}
				break;
			}
		}
		d[index-1].setNbPatient(d[index-1].getNbPatient()-1);
}

//Display all the patient are belongs to a doctor
void displayPatDoctor(int id,vector<Doctor>& d){
	if(Doctor::counter>0){
		if( Doctor::counter>=id && id>0 && d[id-1].getNbPatient()>0 ){
			d[id-1].displayPatients();
		}else if(d[id-1].getNbPatient()==0){
			cout<<"\t-----------------------------------------------\n";
			cout<<"\t| OPS ! This doctor does not have any patient |\n";
			cout<<"\t-----------------------------------------------\n";
		}
		else if(id<=0){
			cout<<"\t--------------------------------------------------------------------\n";
			cout<<"\t|              OPS ! you typed a negative ID                       |\n";
			cout<<"\t--------------------------------------------------------------------\n";
		}else{
				cout<<"\t----------------------------------------------------------------------------------\n";
				cout<<"\t| OPS ! you typed an ID bigger than we have which means the DOCTOR doesn't exist |\n";
				cout<<"\t----------------------------------------------------------------------------------\n";
		}
	}else{
		cout<<"\t-------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no DOCTOR |\n";
		cout<<"\t-------------------------------------------------------------------\n";
	}

}

//Deleting a patient from the table of patients by  CIN
void deletePatient(vector<Patient>& p,string cin,vector<Doctor>& d){
	int index,idDoctor;
	if( Patient::counter>0 ){
		index=searchPatient(p,cin);
		if( index!=-1 ){
			idDoctor=p[index].getidDoctor();
			for(int i=index ; i<Patient::counter-1 ; i++)
				p[i]=p[i+1];
		    delPatientfrList(idDoctor,d,cin);
		    Patient::counter--;
		    cout<<"\t--------------------------------------------\n";
			cout<<"\t| Congratulations ! The patient is deleted |\n";
			cout<<"\t--------------------------------------------\n";	
		}else{
			cout<<"\t---------------------------------------\n";
			cout<<"\t| OPS ! There's no PATIENT with CIN   |\n";
			cout<<"\t---------------------------------------\n";
		}
	}else{
		cout<<"\t--------------------------------------------------------------------\n";
		cout<<"\t| OPS ! you cant perform this operation because there's no PATIENT |\n";
		cout<<"\t--------------------------------------------------------------------\n";
	}
}
//displat all the state 
void displatState(Manager& manager){
		cout<<"\t\t------------------------------------------------------\n";
		cout<<"\t\t|NUMBER OF DOCTORS: "<<Doctor::counter<<endl;
		cout<<"\t\t|NUMBER OF PATIENTS: "<<Patient::counter<<endl;
		cout<<"\t\t|NUMBER OF BOTTLE OF OXYGEN: "<<manager.getNbOxygen()<<endl;
		cout<<"\t\t|NUMBER OF BEDS: "<<manager.getNbBeds()<<endl;
		cout<<"\t\t------------------------------------------------------\n";	
}

//with this menu you can manage the patients inside the hospital
void patientMenu(vector<Doctor>& doctor,vector<Patient>& patient,Manager& manager){
	int nb,choix;
	string cni;
	do{	
		cout<<"\t\t\t\t\t----------------------------------\n";
		cout<<"\t\t\t\t\t|         MANAGE PATIENTS        |\n";
		cout<<"\t\t\t\t\t----------------------------------\n";
		cout<<"\t\t\t\t------------------------------------------------------\n";
		cout<<"\t\t\t\t|ADD ONE PATIENT OR MORE.......... .................1|\n";
		cout<<"\t\t\t\t|SEARCH FOR A PATIENT BY CIN........................2|\n";
		cout<<"\t\t\t\t|DISPLAY THE INFORMATION ABOUT THE DOCTOR...........3|\n";
		cout<<"\t\t\t\t|DELETE A PATIENT BY CIN............................4|\n";
		cout<<"\t\t\t\t|DISPLAY ALL THE PATIENTS...........................5|\n";
		cout<<"\t\t\t\t|RETURN TO THE HOME MENU............................6|\n";
		cout<<"\t\t\t\t------------------------------------------------------\n";	
		cout<<"\t\t\t\t Enter your choice [1-6]: ";
		cin>>choix;
		switch(choix){
			case 1: cout<<"\tENTER HOW MANY PATIENT YOU WANT TO ADD: ";
					cin>>nb;
					addPatients(nb,patient,doctor);
				    break;
			
			case 2: cout<<"\tENTER THE CIN OF THE PATIENT: ";
				    cin>>cni;
				    displayPatientCin(patient,cni);
				    break;
			
			case 3: cout<<"\tENTER THE CIN OF THE PATIENT: ";
				    cin>>cni;
				    displayinfoDoctor(patient,cni,doctor);
				    break;
			
			case 4:  cout<<"\tENTER THE CIN OF THE PATIENT: ";
					 cin>>cni;
					deletePatient(patient,cni,doctor);
				  	 break;	 
			
			case 5: displayPatients(patient);
					break;
			
			case 6: homeMenu(doctor,patient,manager);
					break;			    
		}
		}while(choix>=1 || choix<=6);		   	  	  
}

//with this menu you can manage the doctors inside the hospital
void doctorMenu(vector<Doctor>& doctor,vector<Patient>& patient,Manager& manager){
		int choix,nb,id;
		string cni;
	do{	
		cout<<"\t\t\t\t\t----------------------------------\n";
		cout<<"\t\t\t\t\t|         MANAGE DOCTORS         |\n";
		cout<<"\t\t\t\t\t----------------------------------\n";
		cout<<"\t\t\t\t------------------------------------------------------\n";
		cout<<"\t\t\t\t|ADD ONE DOCTOR OR MORE.............................1|\n";
		cout<<"\t\t\t\t|SEARCH FOR A DOCTOR BY CIN.........................2|\n";
		cout<<"\t\t\t\t|SEARCH FOR A DOCTOR BY ID..........................3|\n";
		cout<<"\t\t\t\t|DISPLAY ALL THE PATIENTS BELONGS TO A DOCTOR.......4|\n";
		cout<<"\t\t\t\t|DELETE A DOCTOR BY ID..............................5|\n";
		cout<<"\t\t\t\t|DISPLAY ALL THE DOCTORS IN THIS HOPITAL..... ......6|\n";
		cout<<"\t\t\t\t|RETURN TO THE HOME MENU............................7|\n";
		cout<<"\t\t\t\t------------------------------------------------------\n";	
		cout<<"\t\t\t\t Enter your choice [1-7]: ";
		cin>>choix;
		switch(choix){
			case 1: cout<<"\tENTER HOW MANY DOCTOR YOU WANT TO ADD: ";
					cin>>nb;
					addDoctor(nb,doctor);
				    break;
			
			case 2: cout<<"\tENTER THE CIN OF THE DOCTOR: ";
				    cin>>cni;
				    displayDoctorCin(doctor,cni);
				    break;
			
			case 3: cout<<"\tENTER THE ID OF THE DOCTOR: ";
				    cin>>id;
				    displayDoctorID(id,doctor);
				    break;
			
			case 4:  cout<<"\tENTER THE ID OF THE DOCTOR: ";
					 cin>>id;
					 displayPatDoctor(id,doctor);
				  	 break;	 
			
			case 5: cout<<"\tENTER THE ID OF THE DOCTOR: ";
					cin>>id;
					deleteDoctor(id,doctor,patient);
					break;
			
			case 6: displayAllDoctors(doctor);
					break;
			case 7: homeMenu(doctor,patient,manager);
					break;						    
		}		   	  	  
		
	}while(choix>=1 || choix<=7);
}

//Manage Hospital menu to display and manipulate the whole materials related to the HOSPITAL
void hospitalMenu(vector<Doctor>& doctor,vector<Patient>& patient,Manager& manager){
	int choix,nb;
	do{	
		cout<<"\t\t\t\t\t\t-------------------\n";
		cout<<"\t\t\t\t\t\t|  MANAGE HOSPITAL |\n";
		cout<<"\t\t\t\t\t\t-------------------\n";
		cout<<"\t\t\t\t----------------------------------------------------\n";
		cout<<"\t\t\t\t|SHOW THE STATE OF THE HOSPITAL...................1|\n";
		cout<<"\t\t\t\t|ADD MORE BOTTLE OF OXYGEN........................2|\n";
		cout<<"\t\t\t\t|ADD MORE BEDS....................................3|\n";
		cout<<"\t\t\t\t|REMOVE THE BOTTLE OF OXYGEN......................4|\n";
		cout<<"\t\t\t\t|REMOVE THE BEDS..................................5|\n";
		cout<<"\t\t\t\t|RETURN TO THE HOME MENU..........................6|\n";
		cout<<"\t\t\t\t----------------------------------------------------\n";	
		cout<<"\t\t\t Enter your choice [1-6]: ";
		cin>>choix;
		switch(choix){
			case 1: displatState(manager);
				  break;
			case 2: cout<<"\tENTER HOW MANY BOTTLE DO YOU WANT TO ADD: ";
				   cin>>nb;
				   manager.setNbOxygen(manager.getNbOxygen()+nb);
				  break;
			case 3: cout<<"\tENTER HOW MANY BEDS DO YOU WANT TO ADD: ";
				    cin>>nb;
				    manager.setNbBeds(manager.getNbBeds()+nb);
					break;
			case 4: cout<<"\tENTER HOW MANY BOTTLE DO YOU WANT TO REMOVE: ";
				    cin>>nb;	
					manager.setNbOxygen(manager.getNbOxygen()-nb);
					break;
			case 5: cout<<"\tHOW MANY BEDS DO YOU WANT TO REMOVE: ";
				    cin>>nb;
					manager.setNbBeds(manager.getNbBeds()-nb);
					break;
			case 6: homeMenu(doctor,patient,manager);				
					break;
				   	  	  
		}
	}while(choix>=1 || choix<=6);
}

//Home menu to display the whole interface about the hospital
void homeMenu(vector<Doctor>& doctor,vector<Patient>& patient,Manager& manager){
	int choix;
	do{	
		cout<<"\t\t\t\t\t--------------------------------\n";
		cout<<"\t\t\t\t\t| WELCOME TO HICHAM'S HOSPITAL |\n";
		cout<<"\t\t\t\t\t--------------------------------\n";
		cout<<"\t\t\t\t----------------------------------------------------\n";
		cout<<"\t\t\t\t|MANAGE DOCTORS...................................1|\n";
		cout<<"\t\t\t\t|MANAGE PATIENTS..................................2|\n";
		cout<<"\t\t\t\t|MANAGE HOSPITAL..................................3|\n";
		cout<<"\t\t\t\t|QUIT APPLICATION.................................4|\n";
		cout<<"\t\t\t\t----------------------------------------------------\n";	
		cout<<"\t\t\t\t Enter your choice [1-3]: ";
		cin>>choix;
		switch(choix){
			case 1: doctorMenu(doctor,patient,manager);
				  break;
			case 2: patientMenu(doctor,patient,manager);
				  break;
			case 3: hospitalMenu(doctor,patient,manager);
				  break;
			case 4: exit(0);
				  break;  
				   	  	  
		}
	}while(choix>=1 || choix<=4);
}

void rules(vector<Doctor>& doctor,vector<Patient>& patient,Manager& manager){
	int nb;
		do{
			cout<<"\t\t\t\t\t\t---------------------------------------------\n";
			cout<<"\t\t\t\t\t\t|   YOU NEED TO READ ALL THEESE STATEMENTS  |\n";
			cout<<"\t\t\t\t\t\t---------------------------------------------\n";
			cout<<"\t\t\t---------------------------------------------------------------------------------------------------------\n";
			cout<<"\t\t\t|1-WHEN YOU ADD A PATIENT AUTOMATICLY WE ASSIGN TO HIM A DOCTOR WHO IS ABLE TO HELP HIM                 |\n";
			cout<<"\t\t\t|  IF THE DOCTOR DOES NOT EXIST YOU CAN'T ADD THIS PATIENT TO OUR HOSPITAL                              |\n";
			cout<<"\t\t\t|2-YOU CAN'T DELETE A DOCTOR IF THERE IS NO OTHER DOCTOR(S) WHO HAS(VE) THE SAME SPECILIATY             |\n";
			cout<<"\t\t\t|3-WHEN YOU DELETE A DOCTOR WHO HAS LIST OF PATIENTS WE MOVE ALL THE PATIENTS TO ANOTHER LIST           |\n";
			cout<<"\t\t\t|  WHICH IS UNDER A DOCTOR WITH THE SAME SPECIALITY WITH HIM AFTER THAT WE CHANGE THE IDS OF ALL DOCTORS|\n";
			cout<<"\t\t\t|  AND ALSO TO ALL THE PATIENTS WHO ARE UNDER EVERY DOCTORS IF THE DOCTOR HAS ONE PATIENT OR MORE       |\n";
			cout<<"\t\t\t|4-WHEN YOU DELETE A PATIENT WE REMVOE HIM FROM THE LIST OF PATEINTS AND ALSO INSIDE THE LIST OF        |\n";
			cout<<"\t\t\t|  PATIENTS WHO ARE UNDER A DOCTOR                                                                      |\n";
			cout<<"\t\t\t|5-YOU CAN MANIPULATE THE WHOLE MATERIALS INSIDE THE HOSPITAL AND THE STATE OF IT                       |\n";
			cout<<"\t\t\t|5-YOU ARE ABLE TO PERFORM SOME METHODS LIKE SEARCHING,MOIFYING... YOU CAN FIGURE OUT THAT IN THE MENUE |\n";
			cout<<"\t\t\t|6-WHEN YOU ADD A NEW PATIENT CHECK THE LIST OF PATIENTS THEN GO TO SEARCH FOR DOCTOR BY ID/CIN TO SEE  |\n";
			cout<<"\t\t\t|  WHAT HAPPEND AND YOU CAN DISPLAY THE WHOLE LIST OF PATIENTS ARE UNDER THIS DOCTOR                    |\n";
			cout<<"\t\t\t|7-YOU CAN'T ADD A PATIENT IF WE DON'T FIND A DOCTOR WHO CAN HELP HIM                                   |\n";
			cout<<"\t\t\t|8-CLICK ON NUMBER 5 TO GO TO THE HOME MENU !                                                           |\n"; 
			cout<<"\t\t\t---------------------------------------------------------------------------------------------------------\n";
			cout<<"\t\t\t: ";
			cin>>nb;	
		}while(nb!=5);
		system("cls");
		homeMenu(doctor,patient,manager);
			
}

int main(){
	vector<Doctor> doctor(100);
	vector<Patient> patient(1000);
	Manager manager(2,4);
	
	rules(doctor,patient,manager);
	return 0;

}

