#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

#include <SDL2/SDL.h>

#include "App.h"
#include "../lector/Lector.hpp"

#include "../log/Log.h"
#include "../log/Error.h"
#include "../log/Debug.h"
#include "../log/Info.h"

const int LARGO_ENTRADA = 150;

void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA]){
	if(cantidadArgumentos==5){
		if(strcmp(argumentos[1],"-c")==0){
			strcpy(direccionLecturaComando,argumentos[2]);
			strcpy(nivelLogEntrada,argumentos[4]);
		}
		else{
			strcpy(direccionLecturaComando,argumentos[4]);
			strcpy(nivelLogEntrada,argumentos[2]);
		}
	}
	else if(cantidadArgumentos == 3){
		if(strcmp(argumentos[1],"-c")==0){
			strcpy(direccionLecturaComando,argumentos[2]);
		}else{
			strcpy(nivelLogEntrada,argumentos[2]);
		}
	}
}

TipoLog* determinarNivelLog(char nivelLogEntrada[LARGO_ENTRADA]){
	if(strcmp(nivelLogEntrada,"Error")==0 || strcmp(nivelLogEntrada,"ERROR")==0 || strcmp(nivelLogEntrada,"error")==0 ){
		return new Error();
	}
	else if(strcmp(nivelLogEntrada,"Debug")==0 || strcmp(nivelLogEntrada,"DEBUG")==0 || strcmp(nivelLogEntrada,"debug")==0 ){
		return new Debug();
	}
	else if(strcmp(nivelLogEntrada,"Info")==0 || strcmp(nivelLogEntrada,"INFO")==0 || strcmp(nivelLogEntrada,"info")==0 ){
		return new Info();
	}
	else{
		return NULL;
	}
}



/* FORMATOS QUE PUEDE RECIBIR
 * /mario -c direccionConfiguracion 				(USAMOS LOG DEL ARCHIVO LEIDO)
 * /mario -l nivelDeLog								(USAMOS CONFIGURACION DEFAULT)
 * /mario -c direccionConfiguracion -l nivelDeLog 	(O AL REVES)
 * /mario 											(USAMOS TODA LA CONFIUGRACION DEFAULT)
 */
int main( int cantidadArgumentos, char* argumentos[] ){

	Lector* lector = new Lector();
	string direccionLecturaDefault = "resources/configuracionDefault.xml";
	char direccionLecturaComando[LARGO_ENTRADA] = "";
	char nivelLogEntrada[LARGO_ENTRADA] = "";
	ArchivoLeido* archivoLeido;
	TipoLog* nivelLog;
	list<string> mensajesError;

	manejarEntrada(cantidadArgumentos, argumentos,direccionLecturaComando,nivelLogEntrada);

	if(strcmp(direccionLecturaComando,"")!=0){
		archivoLeido = lector->leerArchivo(direccionLecturaComando);
		if(!archivoLeido->leidoCorrectamente){
			mensajesError = archivoLeido->mensajeError;
			archivoLeido = lector->leerArchivo(direccionLecturaDefault);
		}
	}
	else{
		archivoLeido = lector->leerArchivo(direccionLecturaDefault);
	}

	if(strcmp(nivelLogEntrada,"")!=0){
		nivelLog = determinarNivelLog(nivelLogEntrada);
		if(nivelLog!=NULL){
			archivoLeido->tipoLog = nivelLog;
		}
	}

	App* aplicacion = App::getInstance(archivoLeido);
	if(!mensajesError.empty()){
		aplicacion->escribirMensajesDeArchivoLeidoEnLog(mensajesError);
	}

	bool salir = false;
	SDL_Event event;
	while(!salir){
		while(SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT ){
				salir = true;
			}
		}
		SDL_PumpEvents();
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		if(keyboard_state_array[SDL_SCANCODE_ESCAPE]){
			salir = true;
		}else{
			aplicacion->actualizar(keyboard_state_array);
		}
		aplicacion->actualizar();
		aplicacion->dibujar();
	}

	delete lector;
	delete aplicacion;
	return 0;
}


