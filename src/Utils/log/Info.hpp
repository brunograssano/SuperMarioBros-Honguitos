#ifndef SRC_UTILS_LOG_INFO_HPP_
#define SRC_UTILS_LOG_INFO_HPP_

#include "TipoLog.hpp"

class Info : public TipoLog{

	public:
		Info()= default;
		~Info() override= default;

		// No hace el nivel de Debug, por lo que las sobreescribe para no hacer nada

		void mostrarPosicion(const std::string& registroPosicion,std::ofstream& archivo) override {};
		void mostrarAccion(const std::string& registroAccion,std::ofstream& archivo) override {};

};


#endif /* SRC_UTILS_LOG_INFO_HPP_ */