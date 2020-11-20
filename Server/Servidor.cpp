#include "Servidor.hpp"

#include <string>

const int TAMANIO_COLA = 4;

Servidor::Servidor(ArchivoLeido* archivoLeido, list<string> mensajesErrorOtroArchivo, int puerto, char* ip){
	int opt = 1;
	struct sockaddr_in address;
	terminoJuego = false;
	log = Log::getInstance(archivoLeido->tipoLog);
	escribirMensajesDeArchivoLeidoEnLog(mensajesErrorOtroArchivo);
	escribirMensajesDeArchivoLeidoEnLog(archivoLeido->mensajeError);

	aplicacionServidor = new AplicacionServidor(archivoLeido->niveles, archivoLeido->cantidadConexiones,
												 archivoLeido->anchoVentana, archivoLeido->altoVentana);

	usuariosValidos = archivoLeido->usuariosValidos;
	if(archivoLeido->cantidadConexiones>MAX_CONEXIONES){
		log->huboUnError("No se permite la cantidad de conexiones enviada ("+to_string(archivoLeido->cantidadConexiones)+"), el maximo es de " + to_string(MAX_CONEXIONES)+".");
		archivoLeido->cantidadConexiones = MAX_CONEXIONES;
	}
	cantidadConexiones = archivoLeido->cantidadConexiones;


	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

    /*Seteamos la ip y el puerto donde estara alojado el servidor*/
    address.sin_port = htons(puerto);
    inet_pton(AF_INET, ip, &address.sin_addr);

    /* Enlazamos el socket acpetador del servidor a la dirección puerto */
    if(bind(socketServer,(struct sockaddr*)&address,sizeof(address))<0){
    	log->huboUnError("No se pudo bindear el socket al puerto.");
		delete archivoLeido;
		delete log;
        exit(EXIT_FAILURE);
    }

	/* Hacemos que el socket sea para escuchar */
	if(listen(socketServer, TAMANIO_COLA) < 0){
		log->huboUnError("No se pudo bindear el socket al puerto.");
		delete archivoLeido;
		delete log;
		exit(EXIT_FAILURE);
	}

    log->mostrarMensajeDeInfo("Se creo el server en la IP: " + (string)ip + " y en el puerto: "+ to_string(puerto) + ". Se estan esperando conexiones");

	delete archivoLeido;
}


void Servidor::escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError){
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}






void* Servidor::escuchar(){
	int usuariosConectados = 0;
	int socketConexionEntrante;
	socklen_t addressStructure;
	struct sockaddr_in addressCliente;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	while(!terminoJuego){

		socketConexionEntrante = accept(socketServer, (struct sockaddr *) &addressCliente, &addressStructure);
		if (socketConexionEntrante < 0){
			pthread_mutex_lock(&mutex);
			log->huboUnError("No se pudo aceptar una conexion proveniente de "+ (string) inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
			pthread_mutex_unlock(&mutex);
		}else{

			pthread_mutex_lock(&mutex);
			log->mostrarMensajeDeInfo("Se obtuvo una conexion de "+ (string) inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+".");
			pthread_mutex_unlock(&mutex);

			ConexionCliente* conexion = new ConexionCliente(this, socketConexionEntrante, this->cantUsuariosLogueados);

			pthread_t hilo;
			if(pthread_create(&hilo, NULL, ConexionCliente::ejecutar_helper, conexion) != 0){
				pthread_mutex_lock(&mutex);
				Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo que escucha al usuario: " + to_string(usuariosConectados)
						+ "\n\t Cliente: " + (string) inet_ntoa(addressCliente.sin_addr) + " ; Puerto: " + to_string(ntohs(addressCliente.sin_port))+ ".");
				pthread_mutex_unlock(&mutex);
			}else{
				pthread_mutex_lock(&mutex);
				Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar al usuario: " + to_string(usuariosConectados)
						+ "\n\t Cliente: " + (string) inet_ntoa(addressCliente.sin_addr) + " ; Puerto: " + to_string(ntohs(addressCliente.sin_port))+ ".");
				pthread_mutex_unlock(&mutex);
			}

			clientes.push_back(conexion);
		}

	}

	return NULL;
}

bool Servidor::esUsuarioValido(usuario_t posibleUsuario){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	for(auto& usuario:usuariosValidos){
		if(posibleUsuario.nombre.compare(usuario.nombre)==0 && posibleUsuario.contrasenia.compare(usuario.contrasenia)==0 && !usuario.usado){
			pthread_mutex_lock(&mutex);
			usuario.usado = true;
			this->cantUsuariosLogueados++;
			for(auto const& cliente:clientes){
				cliente->actualizarCantidadConexiones(this->cantUsuariosLogueados);
			}
			pthread_mutex_unlock(&mutex);
			return true;
		}
	}
	return false;
}


void Servidor::intentarIniciarModelo(){
	while(cantUsuariosLogueados < cantidadConexiones){}
	aplicacionServidor->iniciarJuego();
}

void Servidor::iniciarJuego(){

	pthread_t hiloJuego;
	int resultadoCreate = pthread_create(&hiloJuego, NULL, AplicacionServidor::gameLoop_helper, aplicacionServidor);

	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para el juego, el codigo de error es: " + to_string(resultadoCreate));
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo del juego: (" + to_string(hiloJuego) +").");
	}

}


void Servidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->aplicacionServidor->encolarEntradaUsuario(entradaUsuario);
}

Servidor::~Servidor(){
	for(auto const& cliente:clientes){
		delete cliente;
	}
	clientes.clear();
	close(socketServer);
	delete Log::getInstance();
}
