#ifndef SRC_UTILS_LOG_ERROR_HPP_
#define SRC_UTILS_LOG_ERROR_HPP_

#include "TipoLog.hpp"

class Error : public TipoLog{

	public:
		Error()= default;
		~Error() override= default;

		// No hace los niveles de Debug y Info.

		//DEBUG//
		void mostrarPosicion(const string& registroPosicion,ofstream& archivo)override{};
		void mostrarAccion(const string& registroAccion,ofstream& archivo)override{};

		//INFO//
		void mostrarMensajeDeInfo(const string& registroInfo,ofstream& archivo)override{};
		void mostrarMensajeDeCarga(const string& registroInfo,ofstream& archivo)override{};

};
#endif /* SRC_UTILS_LOG_ERROR_HPP_ */