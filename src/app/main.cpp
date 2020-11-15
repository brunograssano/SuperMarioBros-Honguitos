#include <getopt.h>
#include "../../Server/mainServer.hpp"
#include "../../Client/mainClient.hpp"

const int TERMINO = -1;
#define SERVER 's'


void manejarEntrada(int cantidadArgumentos, char* argumentos[], bool* esServer){
	  static struct option opcionesLargas[] = {
	     {"server", no_argument, 0, 's'},
	     {0, 0, 0, 0}
	  };

	  int argumento;
	  int indiceOpcion = 0;

	  while((argumento = getopt_long(cantidadArgumentos, argumentos, "s", opcionesLargas, &indiceOpcion))!=TERMINO){
	      switch (argumento) {
	          case SERVER:
	        	  (*esServer) = true;
	              break;
	      }
	  }
}

/*
 * FORMATOS QUE PUEDE RECIBIR
 * /mario -s -c direccionConfiguracion -p puerto -i IP					(USAMOS LOG DEL ARCHIVO LEIDO) (-s MODO SERVIDOR)
 * /mario -s -l nivelDeLog -p puerto -i IP								(USAMOS CONFIGURACION DEFAULT)
 * /mario -s -c direccionConfiguracion -l nivelDeLog -p	puerto -i IP 	(O AL REVES)
 * /mario -s -p	puerto -i IP											(SERVER EN CONFIGURACION DEFAULT)
 * /mario 																(PARA CONECTARSE A UN SERVIDOR)
 * /mario -l nivelLog
 */
int main( int cantidadArgumentos, char* argumentos[]){

	bool esServer = false;

	manejarEntrada(cantidadArgumentos, argumentos, &esServer);

	if(esServer){
		mainServer(cantidadArgumentos, argumentos);
	}else{
		mainClient(cantidadArgumentos, argumentos);
	}
}




