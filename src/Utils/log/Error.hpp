#ifndef SRC_UTILS_LOG_ERROR_HPP_
#define SRC_UTILS_LOG_ERROR_HPP_

#include "TipoLog.hpp"

class Error : public TipoLog{

	public:
		Error()= default;
		~Error() override= default;

		// No hace los niveles de Debug y Info.

		//DEBUG//
		void mostrarPosicion(const std::string& registroPosicion,std::ofstream& archivo)override{};
		void mostrarAccion(const std::string& registroAccion,std::ofstream& archivo)override{};

		//INFO//
		void mostrarMensajeDeInfo(const std::string& registroInfo,std::ofstream& archivo)override{};
		void mostrarMensajeDeCarga(const std::string& registroInfo,std::ofstream& archivo)override{};

};
#endif /* SRC_UTILS_LOG_ERROR_HPP_ */