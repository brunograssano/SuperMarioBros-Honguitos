using namespace std;
#include "Lector.h"
#include "pugixml.hpp"
#include <string>
#include <iostream>

string Lector::leerArchivo(char* nombreArchivo){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("modeloXML.xml");
	if (!result){
		return "-1";
	}
	string ancho = "";
    for (pugi::xml_node ventana: doc.child("configuracion").children("ventana"))
    {
    	ancho = ventana.child_value("ancho");
    }
    return ancho;
}


