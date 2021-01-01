#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "../Utils/log/Log.hpp"
#include "UtilidadesServer.hpp"

const int TAMANIO_COLA = 4;

void salir(string mensajeLog){
	Log* log = Log::getInstance();
	cout << "No se pudo iniciar el server, cerrando la aplicacion" << endl;
	log->huboUnError(mensajeLog);
	delete log;
	exit(EXIT_FAILURE);
}

int iniciarSocketServidor(int puerto, char* ip){
	int opt = 1;
	struct sockaddr_in address;
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

void iniciarJuego(pthread_t* hiloJuego,AplicacionServidor* aplicacionServidor){
	int resultadoCreate = pthread_create(hiloJuego, NULL, AplicacionServidor::gameLoop_helper, aplicacionServidor);

	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para el juego, el codigo de error es: " + to_string(resultadoCreate));
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo del juego: (" + to_string(*hiloJuego) +").");
	}

}

void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError){
	Log* log = Log::getInstance();
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}

void crearHiloConectarJugadores(Servidor* servidor){
	pthread_t hiloEscuchar;
	int resultadoCreate = pthread_create(&hiloEscuchar, NULL, Servidor::escuchar_helper, servidor);
	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar, el codigo de error es: " + to_string(resultadoCreate));
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar: (" + to_string(hiloEscuchar) +").");
	}
}

void unirHilosPrincipalYGameLoop(pthread_t* hiloJuego){
	int resultadoJoin = pthread_join((*hiloJuego), NULL);
	if(resultadoJoin != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al juntar los hilos main y gameLoop, el codigo de error es: " + to_string(resultadoJoin));
		pthread_cancel((*hiloJuego));
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se juntaron los hilos main y gameLoop.");
	}
}

void crearHiloReconectarJugadoresFaseInicial(Servidor* servidor){
	pthread_t hilo;
	if (pthread_create(&hilo, NULL, Servidor::reconectarJugadoresFaseInicial_helper, servidor) != 0) {
		Log::getInstance()->huboUnError("No se logro crear el hilo para reconectar los jugadores en fase de inicio.");
	} else {
		Log::getInstance()->mostrarMensajeDeInfo("Se creo el hilo para reconectar los jugadores en fase de inicio correctamente.");
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
