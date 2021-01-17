#include "Servidor.hpp"
#include <string>
#include <cstring>

#define SIN_JUGAR -1

Servidor::Servidor(ArchivoLeido archivoLeido, const list<string>& mensajesErrorOtroArchivo, int puerto, char* ip){
	terminoJuego = false;
	manejadorIDs = new ManejadorIdentificadores();
	log = Log::getInstance(archivoLeido.tipoLog);
	escribirMensajesDeArchivoLeidoEnLog(mensajesErrorOtroArchivo);
	escribirMensajesDeArchivoLeidoEnLog(archivoLeido.mensajeError);

	aplicacionServidor = new AplicacionServidor(this, archivoLeido.niveles, archivoLeido.cantidadConexiones,
												 archivoLeido.anchoVentana, archivoLeido.altoVentana);

	usuariosValidos = archivoLeido.usuariosValidos;
	if(archivoLeido.cantidadConexiones>MAX_CONEXIONES){
		log->huboUnError("No se permite la cantidad de conexiones enviada ("+to_string(archivoLeido.cantidadConexiones)+"), el maximo es de " + to_string(MAX_CONEXIONES)+".");
		archivoLeido.cantidadConexiones = MAX_CONEXIONES;
	}
	cantidadConexiones = archivoLeido.cantidadConexiones;

	socketServer = iniciarSocketServidor(puerto,ip);

    log->mostrarMensajeDeInfo("Se creo el server en la IP: " + (string)ip + " y en el puerto: "+ to_string(puerto) + ". Se estan esperando conexiones");
    aceptadorDeConexiones = new AceptadorDeConexiones(this,socketServer);
    reconectador = new ReconectadorDeConexiones(this);
}


void Servidor::guardarRondaParaEnvio(info_ronda_t ronda){
	for(auto const& parClaveClienteJugando: clientesJugando){
        parClaveClienteJugando.second->agregarMensajeAEnviar(RONDA,&ronda);
	}
}


void Servidor::agregarUsuarioDesconectado(ConexionCliente* conexionPerdida,int idJugador,string nombre,const string& contrasenia){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(!nombre.empty() && !contrasenia.empty() && idJugador!=SIN_JUGAR){
		reconectador->agregarUsuarioDesconectado(nombre,contrasenia,idJugador);
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
                cliente->agregarMensajeAEnviar(MENSAJE_LOG,&mensajeLog);
			}
		}
	}
	pthread_mutex_lock(&mutex);
	conexionesPerdidas.push_front(conexionPerdida);
	clientes.remove(conexionPerdida);
	pthread_mutex_unlock(&mutex);

    mandarActualizacionAClientes();
}

void Servidor::mandarActualizacionAClientes() {
    actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();
    for(auto const& cliente:clientes){
        cliente->actualizarCliente(actualizacion);
    }
}

bool Servidor::empezoElJuego(){
    return aplicacionServidor->empezoElJuego();
}

void Servidor::reconectarJugador(mensaje_log_t mensajeLog,const int idJugador){
    for(auto const parClaveCliente:clientesJugando){
        parClaveCliente.second->agregarMensajeAEnviar(MENSAJE_LOG,&mensajeLog);
    }
    info_partida_t info_partida = aplicacionServidor->obtenerInfoPartida(mapaIDNombre, idJugador);
    nivel_t nivel = aplicacionServidor->obtenerInfoNivel();
    clientesJugando[idJugador]->agregarMensajeAEnviar(PARTIDA,&info_partida);
    clientesJugando[idJugador]->agregarMensajeAEnviar(NIVEL,&nivel);
}

void Servidor::ejecutar(){
	::empezarHilo(aplicacionServidor,"GameLoop");
	::empezarHilo(aceptadorDeConexiones,"AceptadorDeConexiones");
	::empezarHilo(reconectador,"ReconectadorDeConexiones");
	intentarIniciarModelo();
    aplicacionServidor->join("GameLoop");
}

actualizacion_cantidad_jugadores_t Servidor::crearActualizacionJugadores(){ //PASAR A USAR EL MANEJADOR DE KEYS
	actualizacion_cantidad_jugadores_t actualizacion;
	memset(&actualizacion, 0, sizeof(actualizacion_cantidad_jugadores_t));
	int i = 0;

	for(auto const& idNombre:mapaIDNombre){
		par_id_nombre_t par_id_nombre;
		strcpy(par_id_nombre.nombre, idNombre.second.c_str());
		par_id_nombre.id = i;
		par_id_nombre.conectado = !reconectador->estaDesconectado(idNombre.second);

		actualizacion.pares_id_nombre[i] = par_id_nombre;
		i++;
	}
	actualizacion.tope = i;
	actualizacion.cantidadJugadoresActivos = cantUsuariosLogueados;
	actualizacion.cantidadMaximaDeJugadores = cantidadConexiones;
	return actualizacion;
}


bool Servidor::esUsuarioDesconectado(const usuario_t& posibleUsuario, ConexionCliente* conexionClienteConPosibleUsuario){
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int idJugador;
    bool seConecto = false;
    if(reconectador->coincideAlgunaCredencial(posibleUsuario,&idJugador)){
        pthread_mutex_lock(&mutex);
        cantUsuariosLogueados++;
        clientesJugando[idJugador] = conexionClienteConPosibleUsuario;
        conexionClienteConPosibleUsuario->agregarIDJuego(idJugador);
        aplicacionServidor->activarJugador(idJugador);
        pthread_mutex_unlock(&mutex);
        reconectador->despertarHilo();
        seConecto = true;
    }
    return seConecto;
}

bool Servidor::esUsuarioSinConectarse(const usuario_t& posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
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
			despertarHilo();
			return true;
		}
	}
	return false;
}

bool Servidor::esUsuarioValido(const usuario_t& posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
	if(cantUsuariosLogueados>=cantidadConexiones){
		return false;
	}

	return esUsuarioSinConectarse(posibleUsuario,conexionClienteConPosibleUsuario) ||
		   esUsuarioDesconectado(posibleUsuario,conexionClienteConPosibleUsuario);
}


void Servidor::intentarIniciarModelo(){
	info_partida_t info_partida[cantidadConexiones];
	while(mapaIDNombre.size() < cantidadConexiones){
	    dormirHilo();
	}

	log->mostrarMensajeDeInfo("Se va a iniciar el envio de informacion inicial a los jugadores.");

	for(auto parIDCliente:clientesJugando){
		int id = parIDCliente.first;
		info_partida[id] = aplicacionServidor->obtenerInfoPartida(mapaIDNombre,id);
        parIDCliente.second->agregarMensajeAEnviar(PARTIDA,&info_partida[id]);
	}

	aplicacionServidor->iniciarJuego();
}

void Servidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->aplicacionServidor->encolarEntradaUsuario(entradaUsuario);
}

void Servidor::terminarElJuego(){
	for(auto const cliente:conexionesPerdidas){
        cliente->terminarElJuego();
	}
	terminoJuego = true;
}

bool Servidor::terminoElJuego() const{
    return terminoJuego;
}

map<int, string> Servidor::obtenerMapaJugadores() {
    return mapaIDNombre;
}

void Servidor::mandarNivelAClientes(nivel_t nivel) {
    for(auto parClaveCliente: clientesJugando){
        parClaveCliente.second->agregarMensajeAEnviar(NIVEL,&nivel);
    }
}

void Servidor::guardarConexion(ConexionCliente *conexionCliente) {
    clientes.push_back(conexionCliente);
}

int Servidor::cantidadUsuariosLogueados() const {
    return cantUsuariosLogueados;
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

	cerrarServidor(socketServer);
    reconectador->terminarReconectarConexiones();
    reconectador->despertarHilo();
	while(!aceptadorDeConexiones->terminoAceptar() || !reconectador->terminoHiloReconectar()){}
    delete aceptadorDeConexiones;
	delete manejadorIDs;
	delete aplicacionServidor;
	delete reconectador;
	delete log;
}

void Servidor::enviarSonidosA(const int id, list<sonido_t> sonidos) {
    for(auto const& sonido: sonidos){
        if(clientesJugando.count(id) != 0) {
            clientesJugando[id]->agregarMensajeAEnviar(SONIDO, (void *) &sonido);
        }
    }
}
