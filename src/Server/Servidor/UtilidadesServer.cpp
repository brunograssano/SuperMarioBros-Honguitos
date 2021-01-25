#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "src/Utils/log/Log.hpp"
#include "UtilidadesServer.hpp"

const int TAMANIO_COLA = 4;

void salir(const string& mensajeLog){
	Log* log = Log::getInstance();
	cout << "No se pudo iniciar el server, cerrando la aplicacion, mire el log para mas detalles" << endl;
	log->huboUnError(mensajeLog);
	delete log;
	exit(EXIT_FAILURE);
}

int iniciarSocketServidor(int puerto, char* ip){
	int opt = 1;
	struct sockaddr_in address{};
	int socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketServer == 0){
		salir("No se pudo crear el socket para aceptar conexiones");
	}

	if(setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		salir("Ocurrio un error al hacer el setsockopt");
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;

	/*Seteamos la ip y el puerto donde estara alojado el servidor*/
	address.sin_port = htons(puerto);
	inet_pton(AF_INET, ip, &address.sin_addr);

	/* Enlazamos el socket acpetador del servidor a la dirección puerto */
	if(bind(socketServer,(struct sockaddr*)&address,sizeof(address))<0){
		salir("No se pudo bindear el socket al puerto.");
	}

	/* Hacemos que el socket sea para escuchar */
	if(listen(socketServer, TAMANIO_COLA) < 0){
		salir("No se pudo bindear el socket al puerto.");
	}

	cout<< "Se inicio el servidor"<<endl;

	return socketServer;
}

void escribirMensajesDeArchivoLeidoEnLog(const list<string>& mensajesError){
	Log* log = Log::getInstance();
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}

void empezarHilo(Thread* hilo,const string& nombreHilo){
    try{
        hilo->empezarHilo(nombreHilo);
    }catch(const std::exception& e){
        salir("Ocurrio un error creando el hilo "+nombreHilo+", no se va a poder ejecutar el server correctamente. Terminando el servidor");
    }
}

void cerrarServidor(int socketServer){
	int resultado = shutdown(socketServer,SHUT_RDWR);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("No se cerro correctamente el socket del servidor",to_string(errno));
	}
	resultado = close(socketServer);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("No se cerro correctamente el socket del servidor",to_string(errno));
	}
	cout<<"Se cerro el servidor"<<endl;
}


bool coincidenCredenciales(const usuario_t &posibleUsuario,const usuario_t &usuario){
    return posibleUsuario.nombre == usuario.nombre && posibleUsuario.contrasenia == usuario.contrasenia &&
               !usuario.usado;
}