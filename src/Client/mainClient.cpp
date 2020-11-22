#include "../Client/mainClient.hpp"

#include <getopt.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include "../log/Log.hpp"
#include "../log/Error.hpp"
#include "../log/Debug.hpp"
#include "../log/Info.hpp"

#include "../app/AplicacionCliente.hpp"
#include "../Client/Cliente.hpp"



#define LARGO_ENTRADA 150
#define VALOR_MAXIMO_PUERTO 65535
#define VALOR_MINIMO_PUERTO 1023
const int ERROR = -1, VACIO=0, TERMINO = -1;

#define IP 'i'
#define PUERTO 'p'
#define LOG 'l'

void manejarEntrada(int argc, char* args[], char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char nivelLogEntrada[LARGO_ENTRADA]){

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
	          	  strcpy(puertoEntrada,optarg);
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




bool esIpValidaCliente(string ipEntrada){

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

void validarPuertoEIpCliente(string ipEntrada,string puertoEntrada,string ip,int puerto){
	Log* log = Log::getInstance();
	try{
		puerto = stoi(puertoEntrada);
		if(puerto < VALOR_MINIMO_PUERTO && puerto > VALOR_MAXIMO_PUERTO){
			log->huboUnError("El valor de puerto enviado "+ to_string(puerto) +" no es valido");
		}
	}catch(std::exception& e){
		log->huboUnError("El valor de puerto enviado no es valido");
	}
	if(esIpValidaCliente(ipEntrada)){
		ip = ipEntrada;
	}else{
		log->huboUnError("El valor de ip enviado no es valido");
	}
}

int mainClient(int argc, char* args[]){


	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada [LARGO_IP]= "";

	//manejarEntrada(argc, args, ipEntrada, puertoEntrada, nivelLogEntrada);

	int puerto = 5004;
	char ip[] = "127.0.0.1";


	//validarPuertoEIpCliente(ipEntrada,puertoEntrada,ip,puerto);
	TipoLog* nivelLog = determinarNivelLogClient(nivelLogEntrada);
	Log::getInstance(nivelLog);
	info_partida_t informacion; //nos lo mandan

	Cliente* cliente = new Cliente(ip, puerto);
	cliente->ejecutar();
	delete cliente;


	return 0;
}
