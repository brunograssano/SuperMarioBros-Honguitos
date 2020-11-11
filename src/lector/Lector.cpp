#include "Lector.hpp"

#include <vector>
#include <string>
#include <iostream>
#include "ArchivoLeido.hpp"
#include "Parsers/ParserVentana.hpp"
#include "Parsers/ParserLog.hpp"
#include "Parsers/ParserNivel.hpp"
#include "Parsers/ParserUsuario.hpp"
#include "../modelo/Nivel.hpp"

using namespace std;

const int VALOR_POR_DEFECTO_CONEXIONES = 1;

typedef vector<ptrdiff_t> offset_data_t;

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
    offset_data_t::const_iterator iterador = lower_bound(posicionUltimoCaracterPorLinea.begin(), posicionUltimoCaracterPorLinea.end(), offset);
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
		archivoLeido->mensajeError.push_back("El archivo pedido en la direccion: "+ nombreArchivo +" no existe,se carga el archivo por defecto");
		return archivoLeido;
	}

	if (!result){
		offset_data_t posicionUltimoCaracterPorLinea;
		int linea;
		if (calcularPosicionesLinea(posicionUltimoCaracterPorLinea,nombreArchivo.c_str())){
			archivoLeido->leidoCorrectamente = false;
			linea = obtenerLineaError(posicionUltimoCaracterPorLinea,result.offset);
			archivoLeido->mensajeError.push_back("Hay un error en la linea " + to_string(linea)+" del archivo "+ nombreArchivo+",se carga el archivo por defecto");
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("Hubo un error al intentar abrir el archivo "+ nombreArchivo +" cuando se intento determinar el error de la linea,se carga el archivo por defecto");
		}
		return archivoLeido;
	}

    for (pugi::xml_node log: doc.child("configuracion").children("log")){
    	ParserLog* parser = new ParserLog();
		parser->ParsearLog(log,archivoLeido);
		delete parser;
    }

    for (pugi::xml_node ventana: doc.child("configuracion").children("ventana")){
    	ParserVentana* parser = new ParserVentana();
    	parser->ParsearVentana(ventana,archivoLeido);
    	delete parser;
    }

    for (pugi::xml_node niveles: doc.child("configuracion").children("niveles")){
    	for (pugi::xml_node nivel: niveles.children("nivel")){
    		ParserNivel* parser = new ParserNivel();
			parser->ParsearNivel(nivel,archivoLeido);
			delete parser;
    	}
    }
    for (pugi::xml_node credenciales: doc.child("configuracion").children("credenciales")){
		for (pugi::xml_node usuario: credenciales.children("usuario")){
			ParserUsuario* parser = new ParserUsuario();
			parser->parsearUsuario(usuario,archivoLeido);
			delete parser;
		}
	}

    string cantidadConexionesString = doc.child("configuracion").child_value("cantidadConexiones");
    try{
		archivoLeido->cantidadConexiones = stoi(cantidadConexionesString);
		if(archivoLeido->cantidadConexiones<=0){
			archivoLeido->mensajeError.push_back("El valor de cantidad de conexiones ("+cantidadConexionesString+") enviado no puede ser negativo o cero, se carga el valor por defecto");
			archivoLeido->cantidadConexiones = VALOR_POR_DEFECTO_CONEXIONES;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.push_back("El valor de cantidad de conexiones ("+cantidadConexionesString+") enviado no tiene valor valido,se carga el valor por defecto");
		archivoLeido->cantidadConexiones = VALOR_POR_DEFECTO_CONEXIONES;
	}

    archivoLeido->verificarLectura();
    return archivoLeido;

}



