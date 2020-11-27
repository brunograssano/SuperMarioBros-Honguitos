#include "Validaciones.hpp"

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

bool esIpValidaCliente(char ipEntrada[LARGO_IP]){
	/*
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
    }*/
    return true;
}

void validarPuertoEIpCliente(char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char ip[LARGO_IP], int* puerto){
	Log* log = Log::getInstance();
	try{
		*puerto = stoi(puertoEntrada);
		if(*puerto < VALOR_MINIMO_PUERTO && *puerto > VALOR_MAXIMO_PUERTO){
			log->huboUnError("El valor de puerto enviado "+ to_string(*puerto) +" no es valido");
		}
	}catch(std::exception& e){
		log->huboUnError("El valor de puerto enviado no es valido");
	}
	if(esIpValidaCliente(ipEntrada)){
		strcpy(ip,ipEntrada);
	}else{
		log->huboUnError("El valor de ip enviado no es valido");
	}
}



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


bool esIpValida(char ipEntrada[LARGO_IP]){
	/*
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
    }*/
    return false;
}

void validarPuertoEIp(char ipEntrada[LARGO_IP], char puertoEntrada[LARGO_IP], char ip[LARGO_IP], int* puerto){
	Log* log = Log::getInstance();
	try{
		*puerto = stoi(puertoEntrada);
		if(*puerto < VALOR_MINIMO_PUERTO && *puerto > VALOR_MAXIMO_PUERTO){
			log->huboUnError("El valor de puerto enviado "+ to_string(*puerto) +" no es valido");
		}
	}catch(std::exception& e){
		log->huboUnError("El valor de puerto enviado no es valido");
	}
	if(esIpValida(ipEntrada)){
		strcpy(ip,ipEntrada);
	}else{
		log->huboUnError("El valor de ip enviado no es valido");
	}
}


