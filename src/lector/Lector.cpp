#include "Lector.hpp"

#include <libxml++/libxml++.h>
#include <libxml++/parsers/domparser.h>
#include <string>
#include <iostream>
#include "ArchivoLeido.hpp"
#include "Parsers/ParserVentana.hpp"
#include "Parsers/ParserLog.hpp"
#include "Parsers/ParserNivel.hpp"
#include "../modelo/Nivel.h"

using namespace std;
using namespace xmlpp;

typedef std::vector<ptrdiff_t> offset_data_t;

bool calcularPosicionesLinea(offset_data_t& posicionUltimoCaracterPorLinea, const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo){
    	return false;
    }

    ptrdiff_t ultimoCaracterCorrecto = 0;

    char texto[1000];
    int leidos;

    while ((leidos = fread(texto, 1, sizeof(texto), archivo)) > 0){
		for (int i = 0; i < leidos; ++i){
			if (texto[i] == '\n'){
				posicionUltimoCaracterPorLinea.push_back(ultimoCaracterCorrecto + i);
			}
		}
		ultimoCaracterCorrecto += leidos;
    }

    fclose(archivo);

    return true;
}

int obtenerLineaError(const offset_data_t& posicionUltimoCaracterPorLinea, ptrdiff_t offset){
    offset_data_t::const_iterator iterador = std::lower_bound(posicionUltimoCaracterPorLinea.begin(), posicionUltimoCaracterPorLinea.end(), offset);
    size_t linea = iterador - posicionUltimoCaracterPorLinea.begin();

    return 1+linea;
}


ArchivoLeido* Lector::leerArchivo(string nombreArchivo){
	ArchivoLeido* archivoLeido = new ArchivoLeido();
	archivoLeido->leidoCorrectamente = true;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(nombreArchivo.c_str());

	if (!result  && result.status == pugi::status_file_not_found){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El archivo pedido no existe");
		return archivoLeido;
	}

	if (!result){
		offset_data_t posicionUltimoCaracterPorLinea;
		int linea;
		if (calcularPosicionesLinea(posicionUltimoCaracterPorLinea,nombreArchivo.c_str())){
			archivoLeido->leidoCorrectamente = false;
			linea = obtenerLineaError(posicionUltimoCaracterPorLinea,result.offset);
			archivoLeido->mensajeError.push_back("Hay un error en la linea " + to_string(linea));
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("Hubo un error al intentar abrir el archivo");
		}
		return archivoLeido;
	}

    for (pugi::xml_node log: doc.child("configuracion").children("log"))
    {
    	ParserLog* parser = new ParserLog();
		parser->ParsearLog(log,archivoLeido);
		delete parser;
    }

    for (pugi::xml_node ventana: doc.child("configuracion").children("ventana"))
    {
    	ParserVentana* parser = new ParserVentana();
    	parser->ParsearVentana(ventana,archivoLeido);
    	delete parser;
    }

    for (pugi::xml_node niveles: doc.child("configuracion").children("niveles"))
    {
    	for (pugi::xml_node nivel: niveles.children("nivel"))
    	{
    		ParserNivel* parser = new ParserNivel();
			parser->ParsearNivel(nivel,archivoLeido);
			delete parser;
    	}
    }
    archivoLeido->verificarLectura();
    return archivoLeido;

}



