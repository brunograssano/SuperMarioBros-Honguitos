#ifndef SRC_LOG_ERROR_H_
#define SRC_LOG_ERROR_H_

#include "TipoLog.h"

class Error : public TipoLog{

	public:
		Error(){};
		~Error(){};

		// No hace los niveles de Debug y Info.

		//DEBUG//
		void mostrarPosicion(string registroPosicion,ofstream& archivo)override{};
		void mostrarAccion(string registroAccion,ofstream& archivo)override{};

		//INFO//
		void mostrarMensajeDeInfo(string registroInfo,ofstream& archivo)override{};
		void mostrarMensajeDeCarga(string registroInfo,ofstream& archivo)override{};

};
#endif /* SRC_LOG_ERROR_H_ */
