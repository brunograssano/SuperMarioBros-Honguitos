#include "Log.hpp"

#include <ctime>
#include "Debug.hpp"
#include "Error.hpp"
#include "Info.hpp"

Log* Log::log=nullptr;
pthread_mutex_t mutexEscrituraLog = PTHREAD_MUTEX_INITIALIZER;


Log::Log(TipoLog *tipoLog) {
    this->tipoLog = tipoLog;

    string nombreArchivo = "Log - ";
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
void Log::mostrarPosicion(const string& nombreEntidad,int coordenadaX, int coordenadaY){
	pthread_mutex_lock(&mutexEscrituraLog);
	string mensaje = armarMensaje(" - Posicion de " + nombreEntidad ," en (x,y)=(" + to_string(coordenadaX) + "," + to_string(coordenadaY) + ")");
	tipoLog->mostrarPosicion(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

void Log::mostrarAccion(const string& accion){
	pthread_mutex_lock(&mutexEscrituraLog);
	string mensaje = armarMensaje(" - " + accion,"");
	tipoLog->mostrarAccion(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

//INFO//
void Log::mostrarMensajeDeInfo(const string& mensajeInfo){
	pthread_mutex_lock(&mutexEscrituraLog);
	string mensaje = armarMensaje(" - " + mensajeInfo,"");
	tipoLog->mostrarMensajeDeInfo(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

void Log::mostrarMensajeDeCarga(const string& idObjetoCargado,const string& rutaObjetoCargado){
	pthread_mutex_lock(&mutexEscrituraLog);
	string mensaje = armarMensaje(" - Se cargo " + idObjetoCargado, " desde la ruta " + rutaObjetoCargado);
	tipoLog->mostrarMensajeDeCarga(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

//ERRORES//
void Log::huboUnErrorSDL(const string& descripcionError, const string& errorSDL){
	pthread_mutex_lock(&mutexEscrituraLog);
	string mensaje= armarMensaje(" - " + descripcionError, " ---- " + errorSDL);
	tipoLog->huboUnError(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

void Log::huboUnError(const string& descripcionError){
	pthread_mutex_lock(&mutexEscrituraLog);
	string mensaje = armarMensaje(descripcionError,"");
	tipoLog->huboUnError(mensaje, archivoLog);
	pthread_mutex_unlock(&mutexEscrituraLog);
}

string Log::armarMensaje(const string& primeraParte, const string& segundaParte) {
	string mensaje = "";
	time(&tiempo);
	char *tiempoActual = ctime(&tiempo);
	mensaje = mensaje + tiempoActual;
	mensaje = mensaje + primeraParte + segundaParte;
	return mensaje;
}