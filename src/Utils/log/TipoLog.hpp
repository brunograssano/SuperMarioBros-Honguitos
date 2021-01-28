#ifndef SRC_TIPOLOG_H_
#define SRC_TIPOLOG_H_
#include <string>
#include <iostream>
#include <fstream>
#include <utility>

class TipoLog{

	public:

		virtual ~TipoLog()= default;

		//DEBUG//
		virtual void mostrarPosicion(const std::string& registroPosicion,std::ofstream& archivo);
		virtual void mostrarAccion(const std::string& registroAccion,std::ofstream& archivo);

		//INFO//
		virtual void mostrarMensajeDeInfo(const std::string& registroInfo,std::ofstream& archivo);
		virtual void mostrarMensajeDeCarga(const std::string& registroInfo,std::ofstream& archivo);

		//ERRORES//
		virtual void huboUnError(const std::string& registroError,std::ofstream& archivo);


	private:
		static void escribirEnLog(const std::string& tipo,const std::string& registroError,std::ofstream& archivo);

};

#endif /* SRC_TIPOLOG_H_ */