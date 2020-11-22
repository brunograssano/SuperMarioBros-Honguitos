#include "mainServer.hpp"

#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

#include <SDL2/SDL.h>

#include "../app/AplicacionCliente.hpp"
#include "../lector/Lector.hpp"

#include "../log/Log.hpp"
#include "../log/Error.hpp"
#include "../log/Debug.hpp"
#include "../log/Info.hpp"

#include "../Server/Servidor.hpp"

#include <getopt.h>


#define LARGO_ENTRADA 150
#define LARGO_IP 20
#define VALOR_MAXIMO_PUERTO 65535
#define VALOR_MINIMO_PUERTO 1023
const int ERROR = -1, VACIO=0, TERMINO = -1;
#define CONFIG 'c'
#define IP 'i'
#define LOG 'l'
#define PUERTO 'p'

void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],
					char ipEntrada[LARGO_IP],char puertoEntrada[LARGO_IP]){

	  static struct option opcionesLargas[] = {
	     {"config", required_argument, 0, 'c'},
	     {"ip", required_argument, 0, 'i'},
	     {"log", required_argument, 0, 'l'},
	     {"port", required_argument, 0, 'p'},
	     {0, 0, 0, 0}
	  };

	  int argumento;
	  int indiceOpcion = 0;

	  while((argumento = getopt_long(cantidadArgumentos, argumentos, "c:i:p:l:",opcionesLargas, &indiceOpcion))!=TERMINO){
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
	          case PUERTO:
	        	  strcpy(puertoEntrada,optarg);
	              break;
	          default:
	              break;
	      }
	  }
}

TipoLog* determinarNivelLogServer(char nivelLogEntrada[LARGO_ENTRADA]){
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

ArchivoLeido* realizarConfiguracionesIniciales(char direccionLecturaComando[LARGO_ENTRADA], char nivelLogEntrada[LARGO_ENTRADA], list<string> &mensajesErrorOtroArchivo, TipoLog *nivelLog) {
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
		nivelLog = determinarNivelLogServer(nivelLogEntrada);
		if (nivelLog != NULL) {
			archivoLeido->tipoLog = nivelLog;
		}
	}
	delete lector;

	return archivoLeido;
}

bool esIpValida(string ipEntrada){

    if (ipEntrada.length() > 0){

    		vector<string> numeros;
    		string ipAVerificar = ipEntrada;
    		string delimitador = "";
			size_t posicionAnterior = 0;
			size_t posicion = 0;
			do{
				posicion = ipAVerificar.find(delimitador, posicionAnterior);
				if (posicion == string::npos){
					posicion = ipAVerificar.length();
				}
				string numero = ipAVerificar.substr(posicionAnterior, posicion-posicionAnterior);
				if (!numero.empty()){
					numeros.push_back(numero);
				}
				posicionAnterior = posicion + delimitador.length();
			}while (posicion < ipAVerificar.length() && posicionAnterior < ipAVerificar.length());

            if (numeros.size() == 4){
                    for (int i=0; i < 4; i++){
                            for (int j=0; j < numeros[i].length(); j++){
                            	if (!isdigit(numeros[i][j])){
                            		return false;
                            	}
                            }
                            if ((atoi(numeros[i].c_str()) < 0) || (atoi(numeros[i].c_str()) > 255)){
                            	return false;
                            }
                    }
            return true;
            }
    }
    return false;
}

void validarPuertoEIp(string ipEntrada,string puertoEntrada,string ip,int puerto){
	Log* log = Log::getInstance();
	try{
		puerto = stoi(puertoEntrada);
		if(puerto < VALOR_MINIMO_PUERTO && puerto > VALOR_MAXIMO_PUERTO){
			log->huboUnError("El valor de puerto enviado "+ to_string(puerto) +" no es valido");
		}
	}catch(std::exception& e){
		log->huboUnError("El valor de puerto enviado no es valido");
	}
	if(esIpValida(ipEntrada)){
		ip = ipEntrada;
	}else{
		log->huboUnError("El valor de ip enviado no es valido");
	}
}


int mainServer( int cantidadArgumentos, char* argumentos[] ){

	char direccionLecturaComando[LARGO_ENTRADA] = "";
	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada[LARGO_IP] = "";
	ArchivoLeido* archivoLeido;
	TipoLog* nivelLog;
	list<string> mensajesErrorOtroArchivo;

	//manejarEntrada(cantidadArgumentos,argumentos, direccionLecturaComando,nivelLogEntrada,ipEntrada, puertoEntrada);

	int puerto = 5004; //SOLO PARA PROBAR
	char ip[] = "127.0.0.1";
	//validarPuertoEIp(ipEntrada,puertoEntrada,ip,puerto);

	archivoLeido = realizarConfiguracionesIniciales(direccionLecturaComando, nivelLogEntrada, mensajesErrorOtroArchivo, nivelLog);

	Servidor* server = new Servidor(archivoLeido, mensajesErrorOtroArchivo, puerto, ip);
	pthread_t hiloJuego;

	server->iniciarJuego(&hiloJuego);

	pthread_t hilo;
	int resultadoCreate = pthread_create(&hilo, NULL, Servidor::escuchar_helper, server);
	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar, el codigo de error es: " + to_string(resultadoCreate));
		delete server;
		return -1;
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar: (" + to_string(hilo) +").");
	}

	server->intentarIniciarModelo();

	int resultadoJoin = pthread_join(hiloJuego, NULL);
	if(resultadoJoin != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al juntar los hilos main y gameLoop, el codigo de error es: " + to_string(resultadoJoin));
		pthread_cancel(hiloJuego);
		delete server;
		return -1;
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se juntaron los hilos main y gameLoop.");
	}

	delete server;
	return 0;
}
