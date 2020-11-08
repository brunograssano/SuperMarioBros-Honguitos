#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

#include <SDL2/SDL.h>

#include "App.hpp"
#include "../lector/Lector.hpp"

#include "../log/Log.hpp"
#include "../log/Error.hpp"
#include "../log/Debug.hpp"
#include "../log/Info.hpp"

const int LARGO_ENTRADA = 150;

// PREGUNTAR SI SE PUEDE USAR GETOPT PARA HACER MAS FLEXIBLE ESTO

void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],bool* esServer){
	if(cantidadArgumentos==6){ // ASUMO QUE SI TENGO 6 O 4 SE MANDO EL -s de server
		if(strcmp(argumentos[2],"-c")==0){
			strcpy(direccionLecturaComando,argumentos[3]);
			strcpy(nivelLogEntrada,argumentos[5]);
		}
		else{
			strcpy(direccionLecturaComando,argumentos[5]);
			strcpy(nivelLogEntrada,argumentos[3]);
		}
		(*esServer) = true;
	}
	else if(cantidadArgumentos == 4){
		if(strcmp(argumentos[2],"-c")==0){
			strcpy(direccionLecturaComando,argumentos[3]);
		}else{
			strcpy(nivelLogEntrada,argumentos[3]);
		}
		(*esServer) = true;
	}
	else if(cantidadArgumentos==2 && strcmp(argumentos[1],"-s")==0){
		(*esServer) = true;
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

ArchivoLeido* realizarConfiguracionesIniciales(char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],list<string> &mensajesErrorOtroArchivo,TipoLog *nivelLog) {
	Lector* lector = new Lector();
	string direccionLecturaDefault = "resources/ArchivosXML/configuracionDefault.xml";
	ArchivoLeido* archivoLeido;
	if (strcmp(direccionLecturaComando, "") != 0) {
		archivoLeido = lector->leerArchivo(direccionLecturaComando);
		if (!archivoLeido->leidoCorrectamente) {
			mensajesErrorOtroArchivo = archivoLeido->mensajeError;
			delete archivoLeido;
			archivoLeido = lector->leerArchivo(direccionLecturaDefault);
		}
	} else {
		archivoLeido = lector->leerArchivo(direccionLecturaDefault);
	}

	if (strcmp(nivelLogEntrada, "") != 0) {
		nivelLog = determinarNivelLog(nivelLogEntrada);
		if (nivelLog != NULL) {
			archivoLeido->tipoLog = nivelLog;
		}
	}
	delete lector;

	return archivoLeido;
}

void gameLoop(const list<string> &mensajesErrorOtroArchivo, ArchivoLeido *archivoLeido) {
	App *aplicacion = App::getInstance(archivoLeido, mensajesErrorOtroArchivo);
	bool salir = false;
	SDL_Event event;
	while (!salir) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				salir = true;
			}
		}
		SDL_PumpEvents();
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
			salir = true;
		} else {
			aplicacion->actualizar(keyboard_state_array);
		}
		aplicacion->actualizar();
		aplicacion->dibujar();
	}
	delete aplicacion;
}

/* FORMATOS QUE PUEDE RECIBIR
 * /mario -s -c direccionConfiguracion -p puerto -i IP					(USAMOS LOG DEL ARCHIVO LEIDO) (-s MODO SERVIDOR)
 * /mario -s -l nivelDeLog -p	puerto -i IP							(USAMOS CONFIGURACION DEFAULT)
 * /mario -s -c direccionConfiguracion -l nivelDeLog -p	puerto -i IP 	(O AL REVES)
 * /mario -s -p	puerto -i IP											(SERVER EN CONFIGURACION DEFAULT)
 * /mario 																(PARA CONECTARSE A UN SERVIDOR)
 * /mario -l nivelLog ???????????????????????? se puede esto, y la configuracion tambien?
 */
int main( int cantidadArgumentos, char* argumentos[] ){

	char direccionLecturaComando[LARGO_ENTRADA] = "";
	char nivelLogEntrada[LARGO_ENTRADA] = "";
	ArchivoLeido* archivoLeido;
	TipoLog* nivelLog;
	list<string> mensajesErrorOtroArchivo;
	bool esServer = false;

	manejarEntrada(cantidadArgumentos, argumentos,direccionLecturaComando,nivelLogEntrada,&esServer);

	if(esServer){

	}
	else{

	}

	archivoLeido = realizarConfiguracionesIniciales(direccionLecturaComando, nivelLogEntrada, mensajesErrorOtroArchivo, nivelLog);

	gameLoop(mensajesErrorOtroArchivo, archivoLeido);

	return 0;
}


