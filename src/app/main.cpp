#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

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
 * /mario -p puerto -i IP												(PARA CONECTARSE A UN SERVIDOR)
 * /mario -l nivelLog -p puerto -i IP									(LOS PARAMETROS SON COMPLETAMENTE FLEXIBLES)
 */
int main( int cantidadArgumentos, char* argumentos[]){

	bool esServer = true;

	manejarEntrada(cantidadArgumentos, argumentos, &esServer);

	if(esServer){
		mainServer(cantidadArgumentos, argumentos);
	}
	else{
		mainClient(cantidadArgumentos, argumentos);
	}
}

/*
 * Crear hilo con la funcion game loop (puede ser en el server)
 * Para que el server le diga la aplicacion servidor que puede empezar a correr el ciclo
 * Incializar en servidor el objeto, pasarle lo que necesita (parte del archivo leido)
 * */
