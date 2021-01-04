#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <list>
#include "TipoLog.hpp"
using namespace std;

class Log{

	private:
		explicit Log(TipoLog* tipoLog){
			this->tipoLog = tipoLog;

			string nombreArchivo = "Log - ";
			time(&tiempo);
			char* tiempoActual = ctime(&tiempo);
			nombreArchivo = nombreArchivo +tiempoActual;
			nombreArchivo = nombreArchivo + ".txt";
			archivoLog.open("logs/"+nombreArchivo);
		}

		string armarMensaje(const string& primeraParte, const string& segundaParte);

		TipoLog* tipoLog;
		ofstream archivoLog;
		time_t tiempo{};
		static Log* log;

	public:

		static Log* getInstance(TipoLog* tipo);
		static Log* getInstance();
		~Log();

		//DEBUG//
		void mostrarPosicion(const string& nombreEntidad,int coordenadaX, int coordenadaY);
		void mostrarAccion(const string& accion);

		//INFO//
		void mostrarMensajeDeInfo(const string& mensajeInfo);
		void mostrarMensajeDeCarga(const string& idObjetoCargado,const string& rutaObjetoCargado);

		//ERRORES//
		void huboUnErrorSDL(const string& descripcionError, const string& errorSDL);
		void huboUnError(const string& descripcionError);
};



#endif /* SRC_LOG_H_ */
