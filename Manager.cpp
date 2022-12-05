#include"Manager.h"


Manager::Manager(){
	
}

Manager::Manager(int nbOxy,int nbBeds):nbOxygen(nbOxy),nbBeds(nbBeds){
}

Manager::~Manager(){
	
}

int Manager::getNbBeds() const{
	return nbBeds;
}

int Manager::getNbOxygen() const{
	return nbOxygen;
}

void Manager::setNbBeds(int nb){
	nbBeds=nb;
	if(nbBeds<0)
		nbBeds=0;
}

void Manager::setNbOxygen(int nb){
	nbOxygen=nb;
	if(nbOxygen<0)
		nbOxygen=0;
}
