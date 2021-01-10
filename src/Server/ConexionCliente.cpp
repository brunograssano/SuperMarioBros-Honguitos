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
	pthread_t hiloEscuchar;
	pthread_t hiloEnviar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, nullptr, ConexionCliente::escuchar_helper, escuchador);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la informacion del cliente: " + this->ip);
		return; // El hilo de ejecutar muere, y queda dando vueltas solamente el objeto ConexionCliente en la lista
	}

	int resultadoCreateEnviar = pthread_create(&hiloEnviar, nullptr, ConexionCliente::enviar_helper, enviador);
	if(resultadoCreateEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para enviar informacion del servidor al cliente: " + this->ip);
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

bool ConexionCliente::terminoElJuego(){
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

////---------------------------------DESTRUCTOR---------------------------------////

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

void *ConexionCliente::enviar_helper(void *ptr) {
    ((EnviadorConexionCliente*) ptr)->enviar();
    return nullptr;
}

void *ConexionCliente::ejecutar_helper(void *ptr) {
    ((ConexionCliente*) ptr)->ejecutar();
    return nullptr;
}

void *ConexionCliente::escuchar_helper(void *ptr) {
    ((EscuchadorConexionCliente*)ptr)->escuchar();
    return nullptr;
}

string ConexionCliente::obtenerIP() {
    return ip;
}

void ConexionCliente::desconectarse() {
    servidor->agregarUsuarioDesconectado(this,idPropio,nombre,contrasenia);
}
