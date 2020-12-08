#include "Servidor.hpp"
#include <string>
#include <string.h>

#define SIN_JUGAR -1

Servidor::Servidor(ArchivoLeido* archivoLeido, list<string> mensajesErrorOtroArchivo, int puerto, char* ip){
	terminoJuego = false;
	terminoHiloAceptar = false;
	manejadorIDs = new ManejadorIdentificadores();
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

	socketServer = iniciarSocketServidor(puerto,ip);

    log->mostrarMensajeDeInfo("Se creo el server en la IP: " + (string)ip + " y en el puerto: "+ to_string(puerto) + ". Se estan esperando conexiones");

	delete archivoLeido;
}


void Servidor::guardarRondaParaEnvio(info_ronda_t ronda){
	for(auto const& parClaveClienteJugando: clientesJugando){
		parClaveClienteJugando.second->recibirInformacionRonda(ronda);
	}
}


void Servidor::agregarUsuarioDesconectado(ConexionCliente* conexionPerdida,string nombre, string contrasenia,int idJugador){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(!nombre.empty() && !contrasenia.empty() && idJugador!=SIN_JUGAR){
		usuario_t usuarioDesconectado = {nombre,contrasenia,false};
		usuariosQuePerdieronConexion[idJugador] = usuarioDesconectado;
		clientesJugando.erase(idJugador);
		log->mostrarMensajeDeInfo("Se perdio la conexion con el usuario: " + nombre);
		pthread_mutex_lock(&mutex);
		cantUsuariosLogueados--;
		pthread_mutex_unlock(&mutex);
		aplicacionServidor->desconectarJugador(idJugador);

		mensaje_log_t mensajeLog;
		memset(&mensajeLog,0,sizeof(mensaje_log_t));

		nombre.insert(0,"Se desconecto el usuario: ");
		strcpy(mensajeLog.mensajeParaElLog,nombre.c_str());
		mensajeLog.tipo = INFO;
		for(auto const cliente:clientes){
			if(cliente != conexionPerdida){
				cliente->enviarMensajeLog(mensajeLog);
			}
		}
	}
	pthread_mutex_lock(&mutex);
	conexionesPerdidas.push_front(conexionPerdida);
	clientes.remove(conexionPerdida);
	pthread_mutex_unlock(&mutex);

	actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();
	for(auto const& cliente:clientes){
		cliente->actualizarCliente(actualizacion);
	}
}


void Servidor::reconectarJugadoresFaseInicial(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	list<int> idsUsuariosReconectados;
	while(!this->aplicacionServidor->empezoElJuego()){
		for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
			usuario_t usuario = parClaveUsuario.second;
			if(usuario.usado){
				int idJugador = parClaveUsuario.first;
				pthread_mutex_lock(&mutex);
				idsUsuariosReconectados.push_front(idJugador);
				pthread_mutex_unlock(&mutex);
				actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();
				for(auto const& cliente:clientes){
					cliente->actualizarCliente(actualizacion);
				}
			}

		}
		for(auto const id:idsUsuariosReconectados){
			usuariosQuePerdieronConexion.erase(id);
		}
		if(!idsUsuariosReconectados.empty()){
			idsUsuariosReconectados.clear();
		}
	}
}

void Servidor::reconectarJugadoresFaseJuego(){
	list<int> idsUsuariosReconectados;
	while(!terminoJuego){
		for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
			usuario_t usuario = parClaveUsuario.second;
			if(usuario.usado){

				mensaje_log_t mensajeLog;
				memset(&mensajeLog, 0, sizeof(mensaje_log_t));

				usuario.nombre.insert(0, "Se reconecto el usuario: ");
				strcpy(mensajeLog.mensajeParaElLog,usuario.nombre.c_str());
				mensajeLog.tipo = INFO;

				for(auto const parClaveCliente:clientesJugando){
					parClaveCliente.second->enviarMensajeLog(mensajeLog);
				}


				int idJugador = parClaveUsuario.first;
				info_partida_t info_partida = aplicacionServidor->obtenerInfoPartida(mapaIDNombre, idJugador);

				clientesJugando[parClaveUsuario.first]->enviarInfoPartida(info_partida);

				idsUsuariosReconectados.push_front(idJugador);
			}
		}
		for(auto const id:idsUsuariosReconectados){
			usuariosQuePerdieronConexion.erase(id);
		}
		if(!idsUsuariosReconectados.empty()){
			idsUsuariosReconectados.clear();
		}
	}
}

void Servidor::ejecutar(){
	pthread_t hiloJuego;
	iniciarJuego(&hiloJuego,aplicacionServidor);
	crearHiloConectarJugadores(this);
	crearHiloReconectarJugadoresFaseInicial(this);
	intentarIniciarModelo();
	reconectarJugadoresFaseJuego();
}

int Servidor::crearCliente(int socketConexionEntrante,const struct sockaddr_in &addressCliente, int usuariosConectados) {
	if (socketConexionEntrante < 0) {
		log->huboUnError("No se pudo aceptar una conexion proveniente de "+ (string) (inet_ntoa(addressCliente.sin_addr))+ " del puerto "+ to_string(ntohs(addressCliente.sin_port)) + ".");
	} else {
		log->mostrarMensajeDeInfo("Se obtuvo una conexion de "+ (string) (inet_ntoa(addressCliente.sin_addr))+ " del puerto "+ to_string(ntohs(addressCliente.sin_port)) + ".");
		actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();

		ConexionCliente *conexion = new ConexionCliente(this,socketConexionEntrante, this->cantUsuariosLogueados, (string) (inet_ntoa(addressCliente.sin_addr)), actualizacion);

		pthread_t hilo;
		if (pthread_create(&hilo, NULL, ConexionCliente::ejecutar_helper,conexion) != 0) {
			Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo que escucha al usuario: "+ to_string(usuariosConectados) + "\n\t Cliente: "+ (string) (inet_ntoa(addressCliente.sin_addr))
											+ " ; Puerto: " + to_string(ntohs(addressCliente.sin_port)) + ".");
			delete conexion;
		} else {
			Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar al usuario: "+ to_string(usuariosConectados) + "\n\t Cliente: "+ (string) (inet_ntoa(addressCliente.sin_addr))
														+ " ; Puerto: "+ to_string(ntohs(addressCliente.sin_port)) + ".");

			usuariosConectados++;
			clientes.push_back(conexion);
		}
	}

	return usuariosConectados;
}

void Servidor::conectarJugadores(){
	int usuariosConectados = 0;
	int socketConexionEntrante = 0;
	socklen_t addressStructure = 0;
	struct sockaddr_in addressCliente;
	memset(&addressCliente,0,sizeof(sockaddr_in));

	while(!terminoJuego){
		socketConexionEntrante = accept(socketServer, (struct sockaddr *) &addressCliente, &addressStructure);
		if(!terminoJuego){
			usuariosConectados = crearCliente(socketConexionEntrante,addressCliente, usuariosConectados);
		}
	}
	terminoHiloAceptar = true;
}

bool Servidor::estaDesconectado(string nombre){
	bool estaDesconectado = false;
	for(auto const& parClaveUsuario:usuariosQuePerdieronConexion){
		if(nombre == parClaveUsuario.second.nombre && !parClaveUsuario.second.usado){
			estaDesconectado = true;
		}
	}
	return estaDesconectado;
}

actualizacion_cantidad_jugadores_t Servidor::crearActualizacionJugadores(){ //PASAR A USAR EL MANEJADOR DE KEYS
	actualizacion_cantidad_jugadores_t actualizacion;
	memset(&actualizacion, 0, sizeof(actualizacion_cantidad_jugadores_t));
	int i = 0;

	for(auto const& idNombre:mapaIDNombre){
		par_id_nombre_t par_id_nombre;
		strcpy(par_id_nombre.nombre, idNombre.second.c_str());
		par_id_nombre.id = i;
		par_id_nombre.conectado = !estaDesconectado(idNombre.second);

		actualizacion.pares_id_nombre[i] = par_id_nombre;
		i++;
	}
	actualizacion.tope = i;
	actualizacion.cantidadJugadoresActivos = cantUsuariosLogueados;
	actualizacion.cantidadMaximaDeJugadores = cantidadConexiones;
	return actualizacion;
}


bool Servidor::esUsuarioDesconectado(usuario_t posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
		if(coincidenCredenciales(posibleUsuario, parClaveUsuario.second)){
			pthread_mutex_lock(&mutex);
			cantUsuariosLogueados++;
			parClaveUsuario.second.usado = true;
			clientesJugando[parClaveUsuario.first] = conexionClienteConPosibleUsuario;
			conexionClienteConPosibleUsuario->agregarIDJuego(parClaveUsuario.first);
			aplicacionServidor->activarJugador(parClaveUsuario.first);
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
			int id = manejadorIDs->obtenerIDNueva();
			usuario.usado = true;
			clientesJugando[id] = conexionClienteConPosibleUsuario;
			conexionClienteConPosibleUsuario->agregarIDJuego(id);
			mapaIDNombre[id] = posibleUsuario.nombre;
			cantUsuariosLogueados++;
			pthread_mutex_unlock(&mutex);
			actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();
			for(auto const& cliente:clientes){
				cliente->actualizarCliente(actualizacion);
			}
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
	info_partida_t info_partida[cantidadConexiones];
	while(mapaIDNombre.size() < cantidadConexiones){
	}

	log->mostrarMensajeDeInfo("Se va a iniciar el envio de informacion inicial a los jugadores.");

	for(auto parIDCliente:clientesJugando){
		int id = parIDCliente.first;
		info_partida[id] = aplicacionServidor->obtenerInfoPartida(mapaIDNombre,id);
		parIDCliente.second->enviarInfoPartida(info_partida[id]);
	}


	aplicacionServidor->iniciarJuego();
}

void Servidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->aplicacionServidor->encolarEntradaUsuario(entradaUsuario);
}

void Servidor::terminoElJuego(){
	for(auto const cliente:conexionesPerdidas){
		cliente->terminoElJuego();
	}
	terminoJuego = true;
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

	int resultado = shutdown(socketServer,SHUT_RDWR);
	if(resultado<0){
		log->huboUnErrorSDL("No se cerro correctamente el socket del servidor",to_string(errno));
	}
	resultado = close(socketServer);
	if(resultado<0){
		log->huboUnErrorSDL("No se cerro correctamente el socket del servidor",to_string(errno));
	}

	while(!terminoHiloAceptar){}

	delete manejadorIDs;
	delete aplicacionServidor;
	delete log;
}
