#include "ConexionCliente.hpp"
#include "Servidor.hpp"
#include "src/Server/EnviadoresServer/EnviadorConexionCliente.hpp"
#include "src/Server/EscuchadoresServer/EscuchadorConexionCliente.hpp"

ConexionCliente::ConexionCliente(Servidor *servidor, int socket, std::string ip, actualizacion_cantidad_jugadores_t informacionAMandar) {
	this->servidor = servidor;
	this->socket = socket;
	this->ip = std::move(ip);
	this->nombre = "";
	this->contrasenia = "";
    terminoJuego = false;
	recibioCredenciales = false;
	idPropio = SIN_JUGAR;
	escuchador = new EscuchadorConexionCliente(socket,this);
    enviador = new EnviadorConexionCliente(socket,this);
	this->informacionAMandar = informacionAMandar;
}

void ConexionCliente::recibirCredencial(std::string posibleNombre, std::string posibleContrasenia){
	this->nombre = std::move(posibleNombre);
	this->contrasenia = std::move(posibleContrasenia);
	recibioCredenciales = true;
	despertarHilo();
}

void ConexionCliente::esperarCredenciales(){
	while(!recibioCredenciales && !terminoJuego){
	    dormirHilo();
	}
	recibioCredenciales = false;
}

void ConexionCliente::enviarActualizacionesDeRonda(){
	while(!terminoJuego){
        dormirHilo();
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

	agregarMensajeAEnviar(ACTUALIZACION_JUGADORES,&informacionAMandar);
	esperarCredenciales();

	while(!esUsuarioValido && !terminoJuego) {
        esUsuarioValido = servidor->esUsuarioValido({nombre, contrasenia, false}, this);
        agregarMensajeAEnviar(VERIFICACION,&esUsuarioValido);
        if (esUsuarioValido) {
            Log::getInstance()->mostrarMensajeDeInfo(
                    "Se acepto el usuario: " + nombre + " con contrasenia: " + contrasenia + " del cliente: " + ip);
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
    pthread_mutex_lock(&mutex);
	terminoJuego = true;
    pthread_mutex_unlock(&mutex);
    despertarHilo();
}

void ConexionCliente::agregarIDJuego(int IDJugador){
    escuchador->agregarEscuchadorEntrada(IDJugador,servidor);
    idPropio = IDJugador;
}

std::string ConexionCliente::obtenerIP() {
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
		Log::getInstance()->huboUnErrorSDL("Hubo un problema al hacer el shutdown del socket del usuario: "+nombre,std::to_string(errno));
	}
	resultado = close(socket);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("Hubo un problema al hacer el close del socket del usuario: "+nombre,std::to_string(errno));
	}
}