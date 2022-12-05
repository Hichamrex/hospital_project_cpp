#ifndef PERSON_H
#define PERSON_H
#include<string>
#include<istream>
using namespace std;

class Person{
	protected:
		std::string firstName;
		std::string lastName;
		std::string cin;
		std::string phone;
		std::string address;
	public:
	    Person();
		~Person();
		Person(std::string,std::string,std::string,std::string,std::string);	
	    std::string getFname();
	    std::string getLname();
	    std::string getCin();
		std::string getPhone();
	    std::string getAddress();
	    void setFname(std::string);
	    void setLname(std::string);
	    void setCin(std::string);
	    void setPhone(std::string);
	    void setAddress(std::string);
	    
};

#endif
