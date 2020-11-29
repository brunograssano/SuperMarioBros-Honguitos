#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

#include <getopt.h>

#include "Server/mainServer.hpp"
#include "Client/mainClient.hpp"

bool esServer(int cantidadArgumentos, char* argumentos[]){
	bool esServer = false;
	int i=0;
	while(i<cantidadArgumentos && !esServer){
		if(strcmp(argumentos[i],"-s")==0 || strcmp(argumentos[i],"-server")==0 || strcmp(argumentos[i],"--server")==0){
			esServer = false;
		}
		i++;
	}
	return esServer;
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

	// Para usar true / false ir a la línea 12.

	if(esServer(cantidadArgumentos, argumentos)){
		mainServer(cantidadArgumentos, argumentos);
	}
	else{
		mainClient(cantidadArgumentos, argumentos);
	}
}
