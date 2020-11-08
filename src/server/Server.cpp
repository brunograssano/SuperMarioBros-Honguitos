#include "Server.hpp"


const int TAMANIO_COLA = 50;

Server::Server(ArchivoLeido* archivoLeido,list<string> mensajesErrorOtroArchivo, int puerto, int ip){
	int opt = 1;
	struct sockaddr_in address;
	Log* log = Log::getInstance(archivoLeido->tipoLog);
	escribirMensajesDeArchivoLeidoEnLog(mensajesErrorOtroArchivo);
	escribirMensajesDeArchivoLeidoEnLog(archivoLeido->mensajeError);

	/*
	usuariosValidos = archivoLeido->usuariosValidos;
	if(archivoLeido->cantidadConexiones>MAX_CONEXIONES){
		log->huboUnError("No se permite la cantidad de conexiones enviada ("+to_string(archivoLeido->cantidadConexiones)+"), el maximo es de " + to_string(MAX_CONEXIONES)+".");
		archivoLeido->cantidadConexiones = MAX_CONEXIONES;
	}
	cantidadConexiones = archivoLeido->cantidadConexiones;

	*/

	socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if(socketServer == 0){
		log->huboUnError("No se pudo crear el socket para aceptar conexiones");
		delete archivoLeido;
		delete log;
		exit(EXIT_FAILURE);
	}

    if(setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		log->huboUnError("Ocurrio un error al hacer el setsockopt");
		delete archivoLeido;
		delete log;
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(puerto);



    if(bind(socketServer,(struct sockaddr*)&address,sizeof(address))<0){
    	log->huboUnError("No se pudo bindear el socket al puerto.");
		delete archivoLeido;
		delete log;
        exit(EXIT_FAILURE);
    }

    if(listen(socketServer, TAMANIO_COLA) < 0){
    	log->huboUnError("No se pudo bindear el socket al puerto.");
		delete archivoLeido;
		delete log;
		exit(EXIT_FAILURE);
	}


    log->mostrarMensajeDeInfo("Se creo el server, se estan esperando conexiones");

	delete archivoLeido;
}


void Server::escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError){
	Log* log = Log::getInstance();
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}



Server::~Server(){
	delete Log::getInstance();
}
