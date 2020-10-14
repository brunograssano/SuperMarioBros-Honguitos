

#ifndef SRC_LOG_INFO_H_
#define SRC_LOG_INFO_H_

#include "TipoLog.h"

class Info : public TipoLog{

	public:
		Info(){};
		~Info(){};

		// No hace el nivel de Debug, por lo que las sobreescribe para no hacer nada

		void mostrarPosicion(string registroPosicion,ofstream& archivo) override {};
		void mostrarAccion(string registroAccion,ofstream& archivo) override {};

};


#endif /* SRC_LOG_INFO_H_ */
