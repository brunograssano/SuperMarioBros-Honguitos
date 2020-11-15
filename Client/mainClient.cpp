#include "mainClient.hpp"

#include <getopt.h>
#include <string>
#include <string.h>
#include <stdlib.h>

#include <thread>

#include "Cliente.hpp"

const int LARGO_ENTRADA = 150;
const int ERROR = -1, VACIO=0, TERMINO = -1;
#define IP 'i'
#define PUERTO 'p'

void manejarEntrada(int argc, char* args[], char ipEntrada[LARGO_IP], int* puerto){

	  static struct option opcionesLargas[] = {
	     {"ip", required_argument, 0, 'i'},
	     {"puerto", required_argument, 0, 'p'},
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
	        	  char puertoEntrada[LARGO_IP] = "";
	        	  strcpy(puertoEntrada,optarg);
	        	  *puerto = (int) strtol(puertoEntrada, NULL, 10);
	              break;
	      }
	  }
}


int mainClient(int argc, char* args[]){


	char ip[LARGO_IP] = "127.0.0.1";	//TODO: CLI.
	int puerto = 5003;					//TODO: CLI.

	manejarEntrada(argc, args, ip, &puerto);

	Cliente* cliente = new Cliente(ip, puerto);

	pthread_t hiloEscuchar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, NULL, Cliente::escuchar_helper, cliente);
	if(resultadoCreateEscuchar != 0){
		fprintf(stderr, "Ocurrió un error al crear el hilo para escuchar al servidor.");
		delete cliente;
		return -1;
	}

	pthread_t hiloEnviar;
	int resultadoCreateEnviar = pthread_create(&hiloEnviar, NULL, Cliente::enviar_helper, cliente);
	if(resultadoCreateEnviar != 0){
		fprintf(stderr, "Ocurrió un error al crear el hilo para enviar al servidor.");
		delete cliente;
		return -1;
	}

	int resultadoJoinEnviar = pthread_join(hiloEnviar, NULL);
	if(resultadoJoinEnviar != 0){
		fprintf(stderr, "Ocurrió un error al enlazar el hilo \"enviar\" con el main.");
		delete cliente;
		return -1;
	}

	int resultadoJoinEscuchar = pthread_join(hiloEscuchar, NULL);
	if(resultadoJoinEscuchar != 0){
		fprintf(stderr, "Ocurrió un error al enlazar el hilo \"escuchar\" al main.");
		delete cliente;
		return -1;
	}
	return 0;
}
