#include "Servidor.hpp"
#include <string>
#include <cstring>
#include "src/Utils/Constantes.hpp"

#include "UtilidadesServer.hpp"

Servidor::Servidor(const ArchivoLeido& archivoLeido, const std::list<std::string>& mensajesErrorOtroArchivo, int puerto, char* ip)
                    : reconectador(this),
                      iniciadorModelo(archivoLeido.cantidadConexiones,&aplicacionServidor,&clientesJugando,&mapaIDNombre),
                      aceptadorDeConexiones(this,&socketServer),
                      aplicacionServidor(this, archivoLeido.niveles, archivoLeido.cantidadConexiones, archivoLeido.anchoVentana, archivoLeido.altoVentana),
                      manejadorIDs(){
    terminoJuego = false;

    seEnvioUltimoPodio = false;

	log = Log::getInstance(archivoLeido.tipoLog);
	escribirMensajesDeArchivoLeidoEnLog(mensajesErrorOtroArchivo);
	escribirMensajesDeArchivoLeidoEnLog(archivoLeido.mensajeError);

	usuariosValidos = archivoLeido.usuariosValidos;
	cantidadConexiones = archivoLeido.cantidadConexiones;

	socketServer = iniciarSocketServidor(puerto,ip);
    log->mostrarMensajeDeInfo("Se creo el server en la IP: " + (std::string)ip + " y en el puerto: "+ std::to_string(puerto) + ". Se estan esperando conexiones");
}


void Servidor::guardarRondaParaEnvio(info_ronda_t ronda){
	for(auto const& parClaveClienteJugando: clientesJugando){
        parClaveClienteJugando.second->agregarMensajeAEnviar(RONDA,&ronda);
	}
}


void Servidor::agregarUsuarioDesconectado(ConexionCliente* conexionPerdida,int idJugador,std::string nombre,const std::string& contrasenia){
	if(!nombre.empty() && !contrasenia.empty() && idJugador!=SIN_JUGAR){
		reconectador.agregarUsuarioDesconectado(nombre,contrasenia,idJugador);
		clientesJugando.erase(idJugador);
		log->mostrarMensajeDeInfo("Se perdio la conexion con el usuario: " + nombre);
		pthread_mutex_lock(&mutex);
		cantUsuariosLogueados--;
		pthread_mutex_unlock(&mutex);
		aplicacionServidor.desconectarJugador(idJugador);
        notificarClientesDeLaDesconexion(conexionPerdida, nombre);
    }
	pthread_mutex_lock(&mutex);
	conexionesPerdidas.push_front(conexionPerdida);
	clientes.remove(conexionPerdida);
	pthread_mutex_unlock(&mutex);

    mandarActualizacionAClientes();
    despertarHilo();
}

void Servidor::notificarClientesDeLaDesconexion(const ConexionCliente *conexionPerdida, std::string &nombre) {
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

void Servidor::mandarActualizacionAClientes() {
    actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();
    for(auto const& cliente:clientes){
        cliente->agregarMensajeAEnviar(ACTUALIZACION_JUGADORES,&actualizacion);
    }
}

bool Servidor::empezoElJuego(){
    return aplicacionServidor.empezoElJuego();
}

void Servidor::reconectarJugador(mensaje_log_t mensajeLog,const int idJugador){
    for(auto const parClaveCliente:clientesJugando){
        parClaveCliente.second->agregarMensajeAEnviar(MENSAJE_LOG,&mensajeLog);
    }
    info_partida_t info_partida = aplicacionServidor.obtenerInfoPartida(mapaIDNombre, idJugador);
    nivel_t nivel = aplicacionServidor.obtenerInfoNivel();
    clientesJugando[idJugador]->agregarMensajeAEnviar(PARTIDA,&info_partida);
    clientesJugando[idJugador]->agregarMensajeAEnviar(NIVEL,&nivel);
}

void Servidor::ejecutar(){
	::empezarHilo(&aplicacionServidor,"GameLoop");
	::empezarHilo(&aceptadorDeConexiones,"AceptadorDeConexiones");
	::empezarHilo(&reconectador,"ReconectadorDeConexiones");
	::empezarHilo(&iniciadorModelo,"IniciadorDelModelo");
    eliminarConexionesPerdidas();
}

void Servidor::eliminarConexionesPerdidas() {
    while (!terminoJuego){
        while (conexionesPerdidas.empty() && !terminoJuego){
            dormirHilo();
        }
        for(auto const& cliente:conexionesPerdidas){
            delete cliente;
        }
        pthread_mutex_lock(&mutex);
        conexionesPerdidas.clear();
        pthread_mutex_unlock(&mutex);
    }
}

actualizacion_cantidad_jugadores_t Servidor::crearActualizacionJugadores(){
	actualizacion_cantidad_jugadores_t actualizacion;
	memset(&actualizacion, 0, sizeof(actualizacion_cantidad_jugadores_t));
	int i = 0;

	for(auto const& idNombre:mapaIDNombre){
		par_id_nombre_t par_id_nombre;
		strcpy(par_id_nombre.nombre, idNombre.second.c_str());
		par_id_nombre.id = i;
		par_id_nombre.conectado = !reconectador.estaDesconectado(idNombre.second);

		actualizacion.pares_id_nombre[i] = par_id_nombre;
		i++;
	}
	actualizacion.tope = i;
	actualizacion.cantidadJugadoresActivos = cantUsuariosLogueados;
	actualizacion.cantidadMaximaDeJugadores = cantidadConexiones;
	return actualizacion;
}

bool Servidor::esUsuarioDesconectado(const usuario_t& posibleUsuario, ConexionCliente* conexionClienteConPosibleUsuario){
    int idJugador;
    bool seConecto = false;
    if(reconectador.coincideAlgunaCredencial(posibleUsuario,&idJugador)){
        pthread_mutex_lock(&mutex);
        cantUsuariosLogueados++;
        clientesJugando[idJugador] = conexionClienteConPosibleUsuario;
        conexionClienteConPosibleUsuario->agregarIDJuego(idJugador);
        aplicacionServidor.activarJugador(idJugador);
        pthread_mutex_unlock(&mutex);
        reconectador.despertarHilo();
        seConecto = true;
    }
    return seConecto;
}

bool Servidor::esUsuarioSinConectarse(const usuario_t& posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario){
	if(aplicacionServidor.empezoElJuego()){
		return false;
	}

	for(auto& usuario:usuariosValidos){
		if (coincidenCredenciales(posibleUsuario, usuario)) {
			pthread_mutex_lock(&mutex);
			int id = manejadorIDs.obtenerIDNueva();
			usuario.usado = true;
			clientesJugando[id] = conexionClienteConPosibleUsuario;
			conexionClienteConPosibleUsuario->agregarIDJuego(id);
			mapaIDNombre[id] = posibleUsuario.nombre;
			cantUsuariosLogueados++;
			pthread_mutex_unlock(&mutex);
			actualizacion_cantidad_jugadores_t actualizacion = crearActualizacionJugadores();
			for(auto const& cliente:clientes){
				cliente->agregarMensajeAEnviar(ACTUALIZACION_JUGADORES,&actualizacion);
			}
            iniciadorModelo.despertarHilo();
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

void Servidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->aplicacionServidor.encolarEntradaUsuario(entradaUsuario);
}

void Servidor::terminarElJuego(){
	for(auto const cliente:conexionesPerdidas){
        cliente->terminarElJuego();
	}
	terminoJuego = true;
	despertarHilo();
}

bool Servidor::terminoElJuego() const{
    return terminoJuego;
}

std::map<int, std::string> Servidor::obtenerMapaJugadores() {
    return mapaIDNombre;
}

void Servidor::mandarNivelAClientes(nivel_t nivel) {
    for(auto parClaveCliente: clientesJugando){
        parClaveCliente.second->agregarMensajeAEnviar(NIVEL,&nivel);
    }
}

void Servidor::mandarPodiosAClientes(ultimos_podios_t ultimos_podios) {
    if(!seEnvioUltimoPodio) {
        for (auto parClaveCliente: clientesJugando) {
            parClaveCliente.second->agregarMensajeAEnviar(PODIO, &ultimos_podios);
        }
        seEnvioUltimoPodio = true;
    }
}

void Servidor::guardarConexion(ConexionCliente *conexionCliente) {
    clientes.push_back(conexionCliente);
}

void Servidor::enviarSonidosA(const int id, const std::list<sonido_t>& sonidos) {
    for(auto const& sonido: sonidos){
        if(clientesJugando.count(id) != 0) {
            clientesJugando[id]->agregarMensajeAEnviar(SONIDO, (void *) &sonido);
        }
    }
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
    socketServer.cerrar();
    reconectador.terminarReconectarConexiones();
    reconectador.despertarHilo();
	while(!aceptadorDeConexiones.terminoAceptar() || !reconectador.terminoHiloReconectar()){}
	delete log;
    std::cout<<"Se cerro el servidor"<<std::endl;
}
