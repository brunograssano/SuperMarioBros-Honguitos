#include "Validaciones.hpp"
#include <getopt.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "../Utils/log/Debug.hpp"
#include "../Utils/log/Error.hpp"
#include "../Utils/log/Info.hpp"

const int PARTES_DE_IP = 4;
const int TERMINO = -1;
#define VALOR_MAXIMO_PUERTO 65535
#define VALOR_MINIMO_PUERTO 1023

#define SERVER 's'
#define CONFIG 'c'
#define IP 'i'
#define PUERTO 'p'
#define LOG 'l'
#define TEST 't'
#define AYUDA 'h'

void mostrarAyuda(){
    cout<<"Las opciones disponibles son las siguientes"<<endl;
    cout<<"./mario [opciones]"<<endl;
    cout<<"[opciones]"<<endl;
    cout<<"-s,--server Iniciara la aplicacion en modo servidor"<<endl;
    cout<<"-i,--ip Requiere a continuacion de la ip (para conectarse o iniciar un servidor)"<<endl;
    cout<<"-p,--puerto Requiere a continuacion del puerto (para conectarse o iniciar un servidor)"<<endl;
    cout<<"-l,--log Permite cambiar el nivel del log entre error, info, o debug. (Cada uno se puede escribir en los formatos error,Error,ERROR)"<<endl;
    cout<<"-c,--config Solo disponible en modo servidor, requiere de una direccion a un archivo XML a continuacion suyo"<<endl;
    cout<<"-t,--test Correra los tests realizados"<<endl;
    cout<<"-h,--help Muestra esta informacion"<<endl;
    cout<<"Ejemplos"<<endl;
    cout<<"./mario -s --config direccionConfiguracion -p puerto -i IP "<<endl;
    cout<<"./mario -l nivelLog --puerto puerto -i IP"<<endl;
    cout<<"El primer ejemplo iniciara un servidor con las configuraciones indicadas. En el segundo caso se inicia un cliente que se conectara al servidor."<<endl;
}


void manejarEntrada(int argc, char* args[], char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char nivelLogEntrada[LARGO_ENTRADA]){

	  static struct option opcionesLargas[] = {
	     {"ip", required_argument, nullptr, 'i'},
	     {"puerto", required_argument, nullptr, 'p'},
	     {"log", required_argument, nullptr, 'l'},
         {"server", no_argument, nullptr, 's'},
         {"help",no_argument,nullptr,'h'},
		 {nullptr, 0, nullptr, 0}
	  };

	  int argumento;
	  int indiceOpcion = 0;

	  while((argumento = getopt_long(argc, args, "i:p:l:",opcionesLargas, &indiceOpcion))!=TERMINO){
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
              case CONFIG:
                  cout<<"El parametro de configuracion es solo valido en modo servidor"<<endl;
                  break;
              case AYUDA:
                  mostrarAyuda();
                  break;
	          default:
	        	  break;

	      }
	  }
}


void manejarEntrada(int cantidadArgumentos, char* argumentos[],char direccionLecturaComando[LARGO_ENTRADA],char nivelLogEntrada[LARGO_ENTRADA],
					char ipEntrada[LARGO_IP],char puertoEntrada[LARGO_IP]){

	  static struct option opcionesLargas[] = {
	     {"config", required_argument, nullptr, 'c'},
	     {"ip", required_argument, nullptr, 'i'},
	     {"log", required_argument, nullptr, 'l'},
	     {"port", required_argument, nullptr, 'p'},
		 {"server", required_argument, nullptr, 's'},
         {"test",no_argument,nullptr,'t'},
         {"help",no_argument,nullptr,'h'},
	     {nullptr, 0, nullptr, 0}
	  };

	  int argumento;
	  int indiceOpcion = 0;

	  while((argumento = getopt_long(cantidadArgumentos, argumentos, "sc:i:p:l:",opcionesLargas, &indiceOpcion))!=TERMINO){
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
              case AYUDA:
                  mostrarAyuda();
                  break;
	          case TEST:
	              cout<<"Si quiere correr los tests no active el modo servidor"<<endl;
	              break;
	          case SERVER:
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
		return nullptr;
	}
}


bool esIpValida(char ipEntrada[LARGO_IP]){
	string ipAVerificar = ipEntrada;
    if (ipAVerificar.length() > 0){
    		vector<string> numeros;

    		string delimitador = ".";
			size_t posicionAnterior = 0;
			size_t posicion = 0;
			do{
				posicion = ipAVerificar.find(delimitador, posicionAnterior);
				if (posicion >= string::npos){
					posicion = ipAVerificar.length();
				}
				string numero = ipAVerificar.substr(posicionAnterior, posicion-posicionAnterior);
				if (!numero.empty()){
					numeros.push_back(numero);
				}
				posicionAnterior = posicion + delimitador.length();
			}while (posicion < ipAVerificar.length() && posicionAnterior < ipAVerificar.length());

            if (numeros.size() == PARTES_DE_IP){
                    for (int i=0; i < PARTES_DE_IP; i++){
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

void validarPuertoEIp(char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char ip[LARGO_IP], int* puerto){
	try{
		(*puerto) = stoi(puertoEntrada);
		if((*puerto) < VALOR_MINIMO_PUERTO || VALOR_MAXIMO_PUERTO < (*puerto)){
			cout<<"El valor de puerto enviado "+ to_string(*puerto) +" no es valido, esta fuera de rango"<<endl;
			exit(-1);
		}
	}catch(std::exception& e){
		cout<<"El valor de puerto enviado no es valido, no es un numero"<<endl;
		exit(-1);
	}

	if(esIpValida(ipEntrada)){
		strcpy(ip,ipEntrada);
	}else{
		cout<<"El valor de ip enviado no es valido"<<endl;
		exit(-1);
	}
}


