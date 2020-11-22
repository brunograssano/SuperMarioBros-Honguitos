#ifndef SRC_LOG_H_
#define SRC_LOG_H_

using namespace std;
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <list>
#include "TipoLog.hpp"

class Log{

	private:
		Log(TipoLog* tipoLog){
			this->tipoLog = tipoLog;

			string nombreArchivo = "Log - ";
			time(&tiempo);
			char* tiempoActual = ctime(&tiempo);
			nombreArchivo = nombreArchivo +tiempoActual;
			nombreArchivo = nombreArchivo + ".txt";
			archivoLog.open("logs/"+nombreArchivo);
		}

		string armarMensaje(string primeraParte, string segundaParte);

		TipoLog* tipoLog;
		ofstream archivoLog;
		time_t tiempo;
		static Log* log;

	public:

		static Log* getInstance(TipoLog* tipo);
		static Log* getInstance();
		~Log();

		//DEBUG//
		void mostrarPosicion(string nombreEntidad,int coordenadaX, int coordenadaY);
		void mostrarAccion(string accion);

		//INFO//
		void mostrarMensajeDeInfo(string mensajeInfo);
		void mostrarMensajeDeCarga(string idObjetoCargado,string rutaObjetoCargado);

		//ERRORES//
		void huboUnErrorSDL(string descripcionError, string errorSDL);
		void huboUnError(string descripcionError);
};



#endif /* SRC_LOG_H_ */
