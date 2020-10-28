#include <time.h>
#include <stdio.h>
#include <string.h>

#include "Log.h"
#include "Error.h"

Log* Log::log=nullptr;

Log* Log::getInstance(TipoLog* tipo){
	if(log==nullptr){
		if(tipo == NULL){
			tipo = new Error();
		}
		log = new Log(tipo);
	}
	return log;
}
Log* Log::getInstance(){
	if(log==nullptr){
		log = new Log(new Error());
	}
	return log;
}

Log::~Log(){
	delete tipoLog;
	archivoLog.close();
}

//DEBUG//
void Log::mostrarPosicion(string nombreEntidad,int coordenadaX, int coordenadaY){
	string mensaje = armarMensaje(" - Posicion de " + nombreEntidad ," en (x,y)=(" + to_string(coordenadaX) + "," + to_string(coordenadaY) + ")");
	tipoLog->mostrarPosicion(mensaje, archivoLog);
}

void Log::mostrarAccion(string accion){
	string mensaje = armarMensaje(" - " + accion,"");
	tipoLog->mostrarAccion(mensaje, archivoLog);
}

//INFO//
void Log::mostrarMensajeDeInfo(string mensajeInfo){
	string mensaje = armarMensaje(" - " + mensajeInfo,"");
	tipoLog->mostrarMensajeDeInfo(mensaje, archivoLog);
}

void Log::mostrarMensajeDeCarga(string idObjetoCargado,string rutaObjetoCargado){
	string mensaje = armarMensaje(" - Se cargo " + idObjetoCargado, " desde la ruta " + rutaObjetoCargado);
	tipoLog->mostrarMensajeDeCarga(mensaje, archivoLog);;
}

//ERRORES//
void Log::huboUnErrorSDL(string descripcionError, string errorSDL){
	string mensaje= armarMensaje(" - " + descripcionError, " ---- " + errorSDL);
	tipoLog->huboUnError(mensaje, archivoLog);
}

void Log::huboUnError(string descripcionError){
	string mensaje = armarMensaje(descripcionError,"");
	tipoLog->huboUnError(mensaje, archivoLog);
}

string Log::armarMensaje(string primeraParte, string segundaParte) {
	string mensaje = "";
	time(&tiempo);
	char *tiempoActual = ctime(&tiempo);
	mensaje = mensaje + tiempoActual;
	mensaje = mensaje + primeraParte + segundaParte;
	return mensaje;
}



