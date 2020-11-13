#include "Server.hpp"
#include <string>

const int TAMANIO_COLA = 50;

Server::Server(ArchivoLeido* archivoLeido,list<string> mensajesErrorOtroArchivo, int puerto, int ip){
	int opt = 1;
	struct sockaddr_in address;
	log = Log::getInstance(archivoLeido->tipoLog);
	escribirMensajesDeArchivoLeidoEnLog(mensajesErrorOtroArchivo);
	escribirMensajesDeArchivoLeidoEnLog(archivoLeido->mensajeError);


	usuariosValidos = archivoLeido->usuariosValidos;
	if(archivoLeido->cantidadConexiones>MAX_CONEXIONES){
		log->huboUnError("No se permite la cantidad de conexiones enviada ("+to_string(archivoLeido->cantidadConexiones)+"), el maximo es de " + to_string(MAX_CONEXIONES)+".");
		archivoLeido->cantidadConexiones = MAX_CONEXIONES;
	}
	cantidadConexiones = archivoLeido->cantidadConexiones;



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
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}

void Server::escuchar(){
	int usuariosConectados = 0;
	int socketConexionEntrante;
	socklen_t addressStructure;
	struct sockaddr_in addressCliente;
	char buffer[256];
	int estadoLectura;

	while(usuariosConectados<cantidadConexiones){

		socketConexionEntrante = accept(socketServer, (struct sockaddr *) &addressCliente, &addressStructure);
		if (socketConexionEntrante < 0){
			//log->huboUnError("No se pudo aceptar una conexion proveniente de "+ inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
		}
		else{
			//log->mostrarMensajeDeInfo("Se obtuvo una conexion de "+ inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
		}

		send(socketConexionEntrante, "Aceptado\n", 8, 0);

		bzero(buffer,256);//limpia el buffer

		estadoLectura = read(socketConexionEntrante,buffer,255);//usuario // contrasenia //ver como recibimos esto y su pase a usuario_t
		if (estadoLectura < 0){
			//log->huboUnError("No se pudo leer de una conexion proveniente de "+ inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
		}
		else{
			usuario_t posibleUsuario = {"Juan","123"};
			if(esUsuarioValido(posibleUsuario)){
				usuariosConectados++;
				//log->mostrarMensajeDeInfo("Se acepto una conexion de "+ inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
				//agregar un thread a la lista de conexiones
			}
			else{
				//log->mostrarMensajeDeInfo("Se rechazo una conexion de "+ inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
			}
		}

		printf("Here is the message: %s\n",buffer);


	}
}

bool Server::esUsuarioValido(usuario_t posibleUsuario){
	for(auto const& usuario:usuariosValidos){
		if(posibleUsuario.nombre.compare(usuario.nombre)==0 && posibleUsuario.contrasenia.compare(usuario.contrasenia)==0){
			return true;
		}
	}
	return false;
}

Server::~Server(){
	delete Log::getInstance();
}
