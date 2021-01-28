#include "Log.hpp"

#include <ctime>
#include "Debug.hpp"
#include "Error.hpp"
#include "Info.hpp"

Log* Log::log=nullptr;
pthread_mutex_t mutexEscrituraLog = PTHREAD_MUTEX_INITIALIZER;


Log::Log(TipoLog *tipoLog) {
    this->tipoLog = tipoLog;

    std::string nombreArchivo = "Log - ";
    time(&tiempo);
    char* tiempoActual = ctime(&tiempo);
    nombreArchivo = nombreArchivo +tiempoActual;
    nombreArchivo = nombreArchivo + ".txt";
    archivoLog.open("logs/"+nombreArchivo);
}


Log* Log::getInstance(TipoLog* tipo){
	if(log==nullptr){
		if(tipo == nullptr){
			tipo = new Info();
		}
		log = new Log(tipo);
	}
	return log;
}
Log* Log::getInstance(){
	if(log==nullptr){
		log = new Log(new Info());
	}
	return log;
}

Log::~Log(){
	delete tipoLog;
	archivoLog.close();
}

//DEBUG//
void Log::mostrarPosicion(const std::string& nombreEntidad,int coordenadaX, int coordenadaY){
	pthread_mutex_lock(&mutexEscrituraLog);
    std::string mensaje = armarMensaje(" - Posicion de " + nombreEntidad ," en (x,y)=(" + std::to_string(coordenadaX) + "," + std::to_string(coordenadaY) + ")");
	tipoLog->mostrarPosicion(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

void Log::mostrarAccion(const std::string& accion){
	pthread_mutex_lock(&mutexEscrituraLog);
    std::string mensaje = armarMensaje(" - " + accion,"");
	tipoLog->mostrarAccion(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

//INFO//
void Log::mostrarMensajeDeInfo(const std::string& mensajeInfo){
	pthread_mutex_lock(&mutexEscrituraLog);
    std::string mensaje = armarMensaje(" - " + mensajeInfo,"");
	tipoLog->mostrarMensajeDeInfo(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

void Log::mostrarMensajeDeCarga(const std::string& idObjetoCargado,const std::string& rutaObjetoCargado){
	pthread_mutex_lock(&mutexEscrituraLog);
    std::string mensaje = armarMensaje(" - Se cargo " + idObjetoCargado, " desde la ruta " + rutaObjetoCargado);
	tipoLog->mostrarMensajeDeCarga(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

//ERRORES//
void Log::huboUnErrorSDL(const std::string& descripcionError, const std::string& errorSDL){
	pthread_mutex_lock(&mutexEscrituraLog);
    std::string mensaje= armarMensaje(" - " + descripcionError, " ---- " + errorSDL);
	tipoLog->huboUnError(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

void Log::huboUnError(const std::string& descripcionError){
	pthread_mutex_lock(&mutexEscrituraLog);
    std::string mensaje = armarMensaje(descripcionError,"");
	tipoLog->huboUnError(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

std::string Log::armarMensaje(const std::string& primeraParte, const std::string& segundaParte) {
    std::string mensaje = "";
	time(&tiempo);
	char *tiempoActual = ctime(&tiempo);
	mensaje = mensaje + tiempoActual;
	mensaje = mensaje + primeraParte + segundaParte;
	return mensaje;
}