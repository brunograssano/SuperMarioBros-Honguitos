#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <list>
#include "TipoLog.hpp"

class Log{

	private:
		explicit Log(TipoLog* tipoLog);

        std::string armarMensaje(const std::string& primeraParte, const std::string& segundaParte);

		TipoLog* tipoLog;
        std::ofstream archivoLog;
		time_t tiempo{};
		static Log* log;

	public:

		static Log* getInstance(TipoLog* tipo);
		static Log* getInstance();
		~Log();

		//DEBUG//
		void mostrarPosicion(const std::string& nombreEntidad,int coordenadaX, int coordenadaY);
		void mostrarAccion(const std::string& accion);

		//INFO//
		void mostrarMensajeDeInfo(const std::string& mensajeInfo);
		void mostrarMensajeDeCarga(const std::string& idObjetoCargado,const std::string& rutaObjetoCargado);

		//ERRORES//
		void huboUnErrorSDL(const std::string& descripcionError, const std::string& errorSDL);
		void huboUnError(const std::string& descripcionError);
};



#endif /* SRC_LOG_H_ */
