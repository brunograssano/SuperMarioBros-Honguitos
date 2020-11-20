#include "mainClient.hpp"

#include <getopt.h>
#include <string>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "Cliente.hpp"

#include "../src/log/Log.hpp"
#include "../src/log/Error.hpp"
#include "../src/log/Debug.hpp"
#include "../src/log/Info.hpp"

#include "../src/app/App.hpp"



const int LARGO_ENTRADA = 150;
const int ERROR = -1, VACIO=0, TERMINO = -1;

#define IP 'i'
#define PUERTO 'p'
#define LOG 'l'

void manejarEntrada(int argc, char* args[], char ipEntrada[LARGO_IP], int* puerto, char nivelLogEntrada[LARGO_ENTRADA]){

	  static struct option opcionesLargas[] = {
	     {"ip", required_argument, 0, 'i'},
	     {"puerto", required_argument, 0, 'p'},
	     {"log", required_argument, 0, 'l'},
		 {0, 0, 0, 0}
	  };

	  int argumento;
	  int indiceOpcion = 0;

	  while((argumento = getopt_long(argc, args, "i:p:",opcionesLargas, &indiceOpcion))!=TERMINO){
	      switch (argumento) {
	          case IP:
	        	  strcpy(ipEntrada,optarg);
	              break;
	          case PUERTO:
	          	  {
	          		  char puertoEntrada[LARGO_IP] = "";
	          		  strcpy(puertoEntrada,optarg);
	          		  *puerto = (int) strtol(puertoEntrada, NULL, 10);
	          	  }
	        	  break;
	          case LOG:
				  strcpy(nivelLogEntrada,optarg);
				  break;
	          default:
	        	  break;

	      }
	  }
}

TipoLog* determinarNivelLogClient(char nivelLogEntrada[LARGO_ENTRADA]){
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


void gameLoop(info_partida_t informacion,TipoLog* tipoLog,Cliente* cliente) {
	App *aplicacion = App::getInstance(informacion,cliente);
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
			aplicacion->actualizarServer(keyboard_state_array);
		}
		//aplicacion->actualizar();
		aplicacion->dibujar();
	}
	delete aplicacion;
}


int mainClient(int argc, char* args[]){


	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ip[LARGO_IP] = "127.0.0.1";	//TODO: CLI.
	int puerto = 5003;					//TODO: CLI.

	manejarEntrada(argc, args, ip, &puerto, nivelLogEntrada);

	TipoLog* nivelLog = determinarNivelLogClient(nivelLogEntrada);
	Log::getInstance(nivelLog);
	info_partida_t informacion; //nos lo mandan

	Cliente* cliente = new Cliente(ip, puerto);
	cliente->ejecutar();
	delete cliente;


	return 0;
}
