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

	aplicacionServidor = new AplicacionServidor(this, archivoLeido->niveles, archivoLeido->cantidadConexiones,
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

void Servidor::guardarRondaParaEnvio(info_ronda_t ronda){
	for(auto const& parClaveClienteJugando: clientesJugando){
		parClaveClienteJugando.second->recibirInformacionRonda(ronda);
	}
}


void Servidor::agregarUsuarioDesconectado(ConexionCliente* conexionPerdida,string nombre, string contrasenia,int idJugador){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(!nombre.empty() && !contrasenia.empty()){
		usuario_t usuarioDesconectado = {nombre,contrasenia,false};
		usuariosQuePerdieronConexion[idJugador] = usuarioDesconectado;
		clientesJugando.erase(idJugador);
		pthread_mutex_lock(&mutex);
		log->mostrarMensajeDeInfo("Se perdio la conexion con el usuario: " + nombre);
		cantUsuariosLogueados--;
		pthread_mutex_unlock(&mutex);
	}
	conexionesPerdidas.push_front(conexionPerdida);
	clientes.remove(conexionPerdida);


	// Informar a los log de los otros jugadores, usar un mutex con el send, que nadie haga nada
}

void Servidor::ejecutar(){
	pthread_t hiloJuego;
	iniciarJuego(&hiloJuego);

	pthread_t hiloEscuchar;
	int resultadoCreate = pthread_create(&hiloEscuchar, NULL, Servidor::escuchar_helper, this);
	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar, el codigo de error es: " + to_string(resultadoCreate));
		return;
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar: (" + to_string(hiloEscuchar) +").");
	}

	intentarIniciarModelo();

	int resultadoJoin = pthread_join(hiloJuego, NULL);
	if(resultadoJoin != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al juntar los hilos main y gameLoop, el codigo de error es: " + to_string(resultadoJoin));
		pthread_cancel(hiloJuego);
		return;
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se juntaron los hilos main y gameLoop.");
	}

	list<int> idsUsuariosReconectados;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	while(!terminoJuego){
		for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
			usuario_t usuario = parClaveUsuario.second;
			if(usuario.usado){
				int idJugador = parClaveUsuario.first;
				info_partida_t info_partida = aplicacionServidor->obtenerInfoPartida(mapaIDNombre, idJugador);
				pthread_mutex_lock(&mutex);
				clientesJugando[parClaveUsuario.first]->enviarInfoPartida(info_partida);
				pthread_mutex_unlock(&mutex);
				idsUsuariosReconectados.push_front(idJugador);
			}
		}
		for(auto const id:idsUsuariosReconectados){
			usuariosQuePerdieronConexion.erase(id);
		}
	}

	//detach

}

int Servidor::crearCliente(int socketConexionEntrante,const struct sockaddr_in &addressCliente, int usuariosConectados) {
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if (socketConexionEntrante < 0) {
		pthread_mutex_lock(&mutex);
		log->huboUnError("No se pudo aceptar una conexion proveniente de "+ (string) (inet_ntoa(addressCliente.sin_addr))+ " del puerto "+ to_string(ntohs(addressCliente.sin_port)) + ".");
		pthread_mutex_unlock(&mutex);
	} else {
		pthread_mutex_lock(&mutex);
		log->mostrarMensajeDeInfo("Se obtuvo una conexion de "+ (string) (inet_ntoa(addressCliente.sin_addr))+ " del puerto "+ to_string(ntohs(addressCliente.sin_port)) + ".");
		pthread_mutex_unlock(&mutex);
		ConexionCliente *conexion = new ConexionCliente(this,socketConexionEntrante, this->cantUsuariosLogueados, (string) (inet_ntoa(addressCliente.sin_addr)));
		pthread_t hilo;
		if (pthread_create(&hilo, NULL, ConexionCliente::ejecutar_helper,conexion) != 0) {
			pthread_mutex_lock(&mutex);
			Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo que escucha al usuario: "+ to_string(usuariosConectados) + "\n\t Cliente: "+ (string) (inet_ntoa(addressCliente.sin_addr))
											+ " ; Puerto: " + to_string(ntohs(addressCliente.sin_port)) + ".");
			pthread_mutex_unlock(&mutex);
		} else {
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar al usuario: "+ to_string(usuariosConectados) + "\n\t Cliente: "+ (string) (inet_ntoa(addressCliente.sin_addr))
														+ " ; Puerto: "+ to_string(ntohs(addressCliente.sin_port)) + ".");
			pthread_mutex_unlock(&mutex);
		}
		usuariosConectados++;
		clientes.push_back(conexion);
	}
	return usuariosConectados;
}

void Servidor::conectarJugadores(){
	int usuariosConectados = 0;
	int socketConexionEntrante;
	socklen_t addressStructure;
	struct sockaddr_in addressCliente;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	while(!terminoJuego){
		socketConexionEntrante = accept(socketServer, (struct sockaddr *) &addressCliente, &addressStructure);

		if(cantUsuariosLogueados >= cantidadConexiones){
			pthread_mutex_lock(&mutex);
			log->huboUnError("No se pudo aceptar una conexion proveniente de "+ (string) inet_ntoa(addressCliente.sin_addr) + " del puerto "+ to_string(ntohs(addressCliente.sin_port))+"." +
					" porque la cantidad de usuarios logueados es maxima");
			pthread_mutex_unlock(&mutex);
			close(socketConexionEntrante);
		}else{
			usuariosConectados = crearCliente(socketConexionEntrante,addressCliente, usuariosConectados);
		}

	}
}


bool Servidor::esUsuarioDesconectado(usuario_t posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	usuario_t usuario;
	for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
		usuario = parClaveUsuario.second;
		if(coincidenCredenciales(posibleUsuario, usuario)){
			pthread_mutex_lock(&mutex);
			usuario.usado = true;
			clientesJugando[cantUsuariosLogueados] = conexionClienteConPosibleUsuario;
			mapaIDNombre[cantUsuariosLogueados] = posibleUsuario.nombre;
			conexionClienteConPosibleUsuario->agregarIDJuego(cantUsuariosLogueados);
			cantUsuariosLogueados++;
			for(auto const& cliente:clientes){
				cliente->actualizarCantidadConexiones(this->cantUsuariosLogueados);
			}
			pthread_mutex_unlock(&mutex);
			return true;
		}
	}
	return false;
}

bool Servidor::coincidenCredenciales(const usuario_t &posibleUsuario,const usuario_t &usuario) {
	return posibleUsuario.nombre.compare(usuario.nombre) == 0 &&
		   posibleUsuario.contrasenia.compare(usuario.contrasenia) == 0 &&
		   !usuario.usado;
}

bool Servidor::esUsuarioSinConectarse(usuario_t posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
	if(aplicacionServidor->empezoElJuego()){
		return false;
	}

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	for(auto& usuario:usuariosValidos){

		if (coincidenCredenciales(posibleUsuario, usuario)) {
			pthread_mutex_lock(&mutex);

			usuario.usado = true;
			clientesJugando[cantUsuariosLogueados] = conexionClienteConPosibleUsuario;
			conexionClienteConPosibleUsuario->agregarIDJuego(cantUsuariosLogueados);
			mapaIDNombre[cantUsuariosLogueados] = posibleUsuario.nombre;
			cantUsuariosLogueados++;

			for(auto const& cliente:clientes){
				cliente->actualizarCantidadConexiones(cantUsuariosLogueados);
			}

			pthread_mutex_unlock(&mutex);
			return true;
		}
	}
	return false;
}

bool Servidor::esUsuarioValido(usuario_t posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
	if(cantUsuariosLogueados>=cantidadConexiones){
		return false;
	}

	return esUsuarioSinConectarse(posibleUsuario,conexionClienteConPosibleUsuario) ||
		   esUsuarioDesconectado(posibleUsuario,conexionClienteConPosibleUsuario);
}


void Servidor::intentarIniciarModelo(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	info_partida_t info_partida[cantidadConexiones];

	while(cantUsuariosLogueados < cantidadConexiones){}
	pthread_mutex_lock(&mutex);
	log->mostrarMensajeDeInfo("Se va a iniciar el envio de informacion inicial a los jugadores.");
	pthread_mutex_unlock(&mutex);


	for(auto parIDCliente:clientesJugando){
		int id = parIDCliente.first;
		info_partida[id] = aplicacionServidor->obtenerInfoPartida(mapaIDNombre,id);
		parIDCliente.second->enviarInfoPartida(info_partida[id]);
	}


	aplicacionServidor->iniciarJuego();
}

void Servidor::iniciarJuego(pthread_t* hiloJuego){

	int resultadoCreate = pthread_create(hiloJuego, NULL, AplicacionServidor::gameLoop_helper, aplicacionServidor);

	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para el juego, el codigo de error es: " + to_string(resultadoCreate));
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo del juego: (" + to_string(*hiloJuego) +").");
	}

}


void Servidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->aplicacionServidor->encolarEntradaUsuario(entradaUsuario);
}

Servidor::~Servidor(){
	for(auto const& cliente:clientes){
		delete cliente;
	}
	for(auto const& parClaveCliente:clientesJugando){
		delete parClaveCliente.second;
	}
	for(auto const& cliente:conexionesPerdidas){
		delete cliente;
	}
	clientes.clear();
	clientesJugando.clear();
	conexionesPerdidas.clear();
	close(socketServer);
	delete aplicacionServidor;
	delete log;
}
