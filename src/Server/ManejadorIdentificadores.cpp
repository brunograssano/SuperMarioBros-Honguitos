
#include "ManejadorIdentificadores.hpp"


ManejadorIdentificadores::ManejadorIdentificadores(){
	cantidadIDs = 0;
}


int ManejadorIdentificadores::obtenerIDNueva(){
	mapaID.push_back(cantidadIDs);
	cantidadIDs++;
	return mapaID[cantidadIDs-1];
}

vector<int> ManejadorIdentificadores::obtenerTodasLasID(){
	return mapaID;
}

ManejadorIdentificadores::~ManejadorIdentificadores(){
	mapaID.clear();
}
