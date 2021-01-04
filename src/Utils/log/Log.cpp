#include "Log.hpp"

#include <ctime>
#include "Debug.hpp"
#include "Error.hpp"
#include "Info.hpp"

Log* Log::log=nullptr;

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
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	string mensaje = armarMensaje(" - Posicion de " + nombreEntidad ," en (x,y)=(" + to_string(coordenadaX) + "," + to_string(coordenadaY) + ")");
	tipoLog->mostrarPosicion(mensaje, archivoLog);
	pthread_mutex_unlock(&mutex);
}

void Log::mostrarAccion(const string& accion){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	string mensaje = armarMensaje(" - " + accion,"");
	tipoLog->mostrarAccion(mensaje, archivoLog);
	pthread_mutex_unlock(&mutex);
}

//INFO//
void Log::mostrarMensajeDeInfo(const string& mensajeInfo){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	string mensaje = armarMensaje(" - " + mensajeInfo,"");
	tipoLog->mostrarMensajeDeInfo(mensaje, archivoLog);
	pthread_mutex_unlock(&mutex);
}

void Log::mostrarMensajeDeCarga(const string& idObjetoCargado,const string& rutaObjetoCargado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	string mensaje = armarMensaje(" - Se cargo " + idObjetoCargado, " desde la ruta " + rutaObjetoCargado);
	tipoLog->mostrarMensajeDeCarga(mensaje, archivoLog);
	pthread_mutex_unlock(&mutex);
}

//ERRORES//
void Log::huboUnErrorSDL(const string& descripcionError, const string& errorSDL){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	string mensaje= armarMensaje(" - " + descripcionError, " ---- " + errorSDL);
	tipoLog->huboUnError(mensaje, archivoLog);
	pthread_mutex_unlock(&mutex);
}

void Log::huboUnError(const string& descripcionError){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	string mensaje = armarMensaje(descripcionError,"");
	tipoLog->huboUnError(mensaje, archivoLog);
	pthread_mutex_unlock(&mutex);
}

string Log::armarMensaje(const string& primeraParte, const string& segundaParte) {
	string mensaje = "";
	time(&tiempo);
	char *tiempoActual = ctime(&tiempo);
	mensaje = mensaje + tiempoActual;
	mensaje = mensaje + primeraParte + segundaParte;
	return mensaje;
}



