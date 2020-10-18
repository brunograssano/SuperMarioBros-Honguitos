#include <stdio.h>
#include <string>
using namespace std;
#include <SDL2/SDL.h>
#include "App.h"
#include "../lector/Lector.h"

#include "../log/Log.h"
#include "../log/Error.h"

/* FORMATOS QUE PUEDE RECIBIR
 * /mario -c direccionConfiguracion 				(USAMOS LOG DEL ARCHIVO LEIDO)
 * /mario -l nivelDeLog								(USAMOS CONFIGURACION DEFAULT)
 * /mario -c direccionConfiguracion -l nivelDeLog 	(O AL REVES)
 * /mario 											(USAMOS TODA LA CONFIUGRACION DEFAULT)
 */


int main( int cantidadArgumentos, char* argumentos[] ){

	Lector* lector = new Lector();
	string direccionLectura = "resources/configuracionDefault.xml";
	TipoLog* nivelLog;
	if(cantidadArgumentos==5){
		if(strcmp(argumentos[1],"-c")){
			direccionLectura = argumentos[2];
			//nos quedamos con el nivel del log en argumentos[4]
		}
		else{
			direccionLectura = argumentos[4];
			//nos quedamos con el nivel del log en argumentos[2]
		}
	}
	else if(cantidadArgumentos == 3){
		if(strcmp(argumentos[1],"-c")){
			direccionLectura = argumentos[2];
		}else{
			// TODO nos quedamos con el nivel del log que nos mandan?
		}
	}


	ArchivoLeido* archivoLeido = lector->leerArchivo(direccionLectura);
	if(archivoLeido == NULL){
		Log* log = Log::getInstance(new Error());
		log->huboUnError("No se pudo encontrar la configuacion en: " +  direccionLectura);
		delete log;
		delete lector;
		return 0;
	}


	App* aplicacion = App::GetInstance(archivoLeido);

	bool salir = false;
	SDL_Event evento;
	while(!salir){
		while(SDL_PollEvent( &evento ) != 0){
			if( evento.type == SDL_QUIT ){
				salir = true;
			}else{
				aplicacion->actualizar(evento);
			}
		}
		aplicacion->actualizar();
		aplicacion->dibujar();
	}

	delete lector;
	delete aplicacion;
	return 0;
}


