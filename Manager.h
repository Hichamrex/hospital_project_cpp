#ifndef MANAGER_H
#define MANAGER_H
#include<string>
class Manager{
   private:
	int nbOxygen;
	int nbBeds;
   public:
   	 Manager();
	 ~Manager();
	 Manager(int,int);
	 int getNbOxygen() const;
	 int getNbBeds() const;
	 void setNbOxygen(int);
	 void setNbBeds(int);	
};

#endif
