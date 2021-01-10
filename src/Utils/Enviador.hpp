#ifndef SRC_UTILS_ENVIADOR_HPP_
#define SRC_UTILS_ENVIADOR_HPP_


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Utils.hpp"

#include "../Utils/log/Log.hpp"

#include <iostream>

#include <string>
#include <cstring>

#include <unistd.h>

class Enviador{
	public:
		virtual ~Enviador()= default;
		virtual void enviar() = 0;
		virtual void dejarInformacion(void* informacion) = 0;

	protected:
        void enviar(char caracter,const void* structPointer, unsigned int bytes);
        static void revisarSiSeMandoCorrectamente(int resultado, const string& descripcion);
        static void casoError(const string& descripcion);
        static void casoSocketCerrado(const string& descripcion);
        static void casoExitoso(const string& descripcion);
		int socket{};
};


#endif /* SRC_UTILS_ENVIADOR_HPP_ */
