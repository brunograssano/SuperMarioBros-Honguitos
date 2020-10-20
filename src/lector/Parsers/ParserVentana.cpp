#include "ParserVentana.hpp"


void ParserVentana::ParsearVentana(pugi::xml_node ventana,ArchivoLeido* archivoLeido){
	string ancho = ventana.child_value("ancho");
	string alto = ventana.child_value("alto");
	if(ancho.compare("")!=0){
		archivoLeido->anchoVentana = stoi(ancho);
	}
	if(alto.compare("")!=0){
		archivoLeido->altoVentana = stoi(alto);
	}
}

