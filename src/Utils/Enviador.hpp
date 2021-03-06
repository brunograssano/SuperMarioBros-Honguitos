#ifndef SRC_UTILS_ENVIADOR_HPP_
#define SRC_UTILS_ENVIADOR_HPP_

#include "Socket.hpp"
#include <string>
#include <cstring>
#include <unistd.h>

class Enviador{
	public:
		virtual ~Enviador()= default;
		virtual void enviar() = 0;
		virtual void dejarInformacion(void* informacion) = 0;

	protected:
        void enviar(char caracter,void* structPointer, unsigned int bytes);
        static void revisarSiSeMandoCorrectamente(int resultado, const std::string& descripcion);
        static void casoError(const std::string& descripcion);
        static void casoSocketCerrado(const std::string& descripcion);
        static void casoExitoso(const std::string& descripcion);
		Socket* socket{};
};


#endif /* SRC_UTILS_ENVIADOR_HPP_ */
