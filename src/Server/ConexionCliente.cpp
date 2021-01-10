#include "ConexionCliente.hpp"
#define SIN_JUGAR -1

pthread_cond_t variableCondicionalConexionCliente=PTHREAD_COND_INITIALIZER;

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, /*todo: sacar*/int cantidadConexiones,string ip, actualizacion_cantidad_jugadores_t informacionAMandar){
	this->servidor = servidor;
	this->socket = socket;
	this->ip = std::move(ip);
	this->cantidadConexiones = cantidadConexiones;
	this->nombre = "";
	this->contrasenia = "";
	puedeJugar = false;
	terminoJuego = false;
	recibioCredenciales = false;
	idPropio = SIN_JUGAR;
	escuchador = new EscuchadorConexionCliente(socket,this);
    enviador = new EnviadorConexionCliente(socket,this);
	this->informacionAMandar = informacionAMandar;
}

void ConexionCliente::recibirCredencial(string posibleNombre, string posibleContrasenia){
	this->nombre = std::move(posibleNombre);
	this->contrasenia = std::move(posibleContrasenia);
	recibioCredenciales = true;
}

void ConexionCliente::esperarCredenciales(){
    pthread_mutex_t mutexServer = PTHREAD_MUTEX_INITIALIZER;
	while(!recibioCredenciales && !terminoJuego){
	}
	recibioCredenciales = false;
}

void ConexionCliente::enviarActualizacionesDeRonda() const{
    pthread_mutex_t mutexServer = PTHREAD_MUTEX_INITIALIZER;
	while(!terminoJuego){
        pthread_mutex_lock(&mutexServer);
        pthread_cond_wait(&variableCondicionalConexionCliente, &mutexServer);
        pthread_mutex_unlock(&mutexServer);
	}
}

void ConexionCliente::ejecutar(){
	try{
        enviador->empezarHilo("Enviador");
        escuchador->empezarHilo("Escuchador");
	}catch(const std::exception& e){
        terminoJuego = true;
        return;
	}

	bool esUsuarioValido = false;

	actualizarCliente(informacionAMandar);
	esperarCredenciales();

	while(!esUsuarioValido && !terminoJuego) {
        esUsuarioValido = servidor->esUsuarioValido({nombre, contrasenia, false}, this);
        agregarMensajeAEnviar(VERIFICACION,&esUsuarioValido);
        if (esUsuarioValido) {
            Log::getInstance()->mostrarMensajeDeInfo(
                    "Se acepto el usuario: " + nombre + " con contrasenia: " + contrasenia + " del cliente: " +
                    this->ip);
        } else {
            esperarCredenciales();
        }
    }
	enviarActualizacionesDeRonda();
}

void ConexionCliente::agregarMensajeAEnviar(char caracter,void* mensaje) {
    enviador->agregarMensajeAEnviar(caracter,mensaje);
}

bool ConexionCliente::terminoElJuego() const{
    return terminoJuego;
}

void ConexionCliente::terminarElJuego(){
    pthread_mutex_t mutexServer = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutexServer);
	terminoJuego = true;
    pthread_cond_signal(&variableCondicionalConexionCliente);
    pthread_mutex_unlock(&mutexServer);
}

void ConexionCliente::agregarIDJuego(int IDJugador){
    escuchador->agregarEscuchadorEntrada(IDJugador,servidor);
	puedeJugar = true;
	idPropio = IDJugador;
}

void ConexionCliente::actualizarCliente(actualizacion_cantidad_jugadores_t actualizacion){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	this->cantidadConexiones = actualizacion.cantidadJugadoresActivos;
    pthread_mutex_unlock(&mutex);
    agregarMensajeAEnviar(ACTUALIZACION_JUGADORES,&actualizacion);
}

string ConexionCliente::obtenerIP() {
    return ip;
}

void ConexionCliente::desconectarse() {
    servidor->agregarUsuarioDesconectado(this,idPropio,nombre,contrasenia);
}

ConexionCliente::~ConexionCliente(){
    delete escuchador;
	delete enviador;

	int resultado = shutdown(socket, SHUT_RDWR);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("Hubo un problema al hacer el shutdown del socket del usuario: "+nombre,to_string(errno));
	}
	resultado = close(socket);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("Hubo un problema al hacer el close del socket del usuario: "+nombre,to_string(errno));
	}
}