#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

#include <getopt.h>

#include "Server/mainServer.hpp"
#include "Client/mainClient.hpp"

void manejarEntrada(int cantidadArgumentos, char* argumentos[], bool* esServer){
	for(int i=0;i<cantidadArgumentos;i++){
		if(strcmp(argumentos[i],"-s")==0 || strcmp(argumentos[i],"-server")==0 || strcmp(argumentos[i],"--server")==0){
			(*esServer) = true;
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

	bool esServer = false;

	manejarEntrada(cantidadArgumentos, argumentos, &esServer);

	if(esServer){
		mainServer(cantidadArgumentos, argumentos);
	}
	else{
		mainClient(cantidadArgumentos, argumentos);
	}
}
