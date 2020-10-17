using namespace std;
#include "Lector.h"
#include "pugixml.hpp"
#include <string>
#include <iostream>

string Lector::leerArchivo(string nombreArchivo){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(nombreArchivo.c_str());
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


