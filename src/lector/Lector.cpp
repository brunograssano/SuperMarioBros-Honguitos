#include "Lector.h"
#include "pugixml.hpp"
#include <string>
#include <iostream>
#include "ArchivoLeido.hpp"
#include "ParserVentana.hpp"
#include "ParserLog.hpp"
#include "ParserNivel.hpp"
#include "../modelo/Nivel.h"

using namespace std;

ArchivoLeido* Lector::leerArchivo(string nombreArchivo){
	ArchivoLeido* archivoLeido = new ArchivoLeido();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(nombreArchivo.c_str());
	if (!result){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El archivo pedido no existe");
		return archivoLeido;
	}

    for (pugi::xml_node log: doc.child("configuracion").children("log"))
    {
    	ParserLog* parser = new ParserLog();
		parser->ParsearLog(log,archivoLeido);
    }

    for (pugi::xml_node ventana: doc.child("configuracion").children("ventana"))
    {
    	ParserVentana* parser = new ParserVentana();
    	parser->ParsearVentana(ventana,archivoLeido);
    }

    for (pugi::xml_node niveles: doc.child("configuracion").children("niveles"))
    {
    	for (pugi::xml_node nivel: niveles.children("nivel"))
    	{
    		ParserNivel* parser = new ParserNivel();
			parser->ParsearNivel(nivel,archivoLeido);
    	}
    }
    archivoLeido->verificarLectura();
    return archivoLeido;
}


