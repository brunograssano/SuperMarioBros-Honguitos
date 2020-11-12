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

#include "../server/Server.hpp"

#include <getopt.h>

const int LARGO_ENTRADA = 150,LARGO_IP = 20;
const int ERROR = -1, VACIO=0, TERMINO = -1;
#define CONFIG 'c'
#define IP 'i'
#define LOG 'l'
#define SERVER 's'
#define PUERTO 'p'

void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],
					char ipEntrada[LARGO_IP],char puertoEntrada[LARGO_IP],bool* esServer){

	  static struct option opcionesLargas[] = {
	     {"config", required_argument, 0, 'c'},
	     {"ip", required_argument, 0, 'i'},
	     {"log", required_argument, 0, 'l'},
	     {"port", required_argument, 0, 'p'},
	     {"server", no_argument, 0, 's'},
	     {0, 0, 0, 0}
	  };

	  int argumento;
	  int indiceOpcion = 0;

	  while((argumento = getopt_long(cantidadArgumentos, argumentos, "c:i:p:l:s",opcionesLargas, &indiceOpcion))!=TERMINO){
	      switch (argumento) {
	          case CONFIG:
	        	  strcpy(direccionLecturaComando,optarg);
	              break;
	          case IP:
	        	  strcpy(ipEntrada,optarg);
	              break;
	          case LOG:
	              strcpy(nivelLogEntrada,optarg);
	              break;
	          case SERVER:
	        	  (*esServer) = true;
	              break;
	          case PUERTO:
	        	  strcpy(puertoEntrada,optarg);
	              break;
	          default:
	              break;
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
 * /mario -s -l nivelDeLog -p puerto -i IP								(USAMOS CONFIGURACION DEFAULT)
 * /mario -s -c direccionConfiguracion -l nivelDeLog -p	puerto -i IP 	(O AL REVES)
 * /mario -s -p	puerto -i IP											(SERVER EN CONFIGURACION DEFAULT)
 * /mario 																(PARA CONECTARSE A UN SERVIDOR)
 * /mario -l nivelLog
 */
int main( int cantidadArgumentos, char* argumentos[] ){

	char direccionLecturaComando[LARGO_ENTRADA] = "";
	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada[LARGO_IP] = "";
	ArchivoLeido* archivoLeido;
	TipoLog* nivelLog;
	list<string> mensajesErrorOtroArchivo;
	bool esServer = false;

	manejarEntrada(cantidadArgumentos, argumentos,direccionLecturaComando,nivelLogEntrada,ipEntrada,puertoEntrada,&esServer);

	if(esServer){
		// hacer parseo de la ip
		int puerto=8080;
		int ip=192456;
		Server* server = new Server(archivoLeido,mensajesErrorOtroArchivo, puerto,ip);
		server->escuchar();
	}
	else{

	}

	archivoLeido = realizarConfiguracionesIniciales(direccionLecturaComando, nivelLogEntrada, mensajesErrorOtroArchivo, nivelLog);

	gameLoop(mensajesErrorOtroArchivo, archivoLeido);

	return 0;
}


