#include "ManejadorIdentificadores.hpp"

ManejadorIdentificadores::ManejadorIdentificadores(){
	cantidadIDs = 0;
}


int ManejadorIdentificadores::obtenerIDNueva(){
	mapaID.push_back(cantidadIDs);
	cantidadIDs++;
	return mapaID[cantidadIDs-1];
}

ManejadorIdentificadores::~ManejadorIdentificadores(){
	mapaID.clear();
}
