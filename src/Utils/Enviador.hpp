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
#include <string.h>

#include <unistd.h>

class Enviador{
	public:
		virtual ~Enviador(){};
		virtual void enviar() = 0;
		virtual void dejarInformacion(void* informacion) = 0;

		void revisarSiSeMandoCorrectamente(int resultado, string descripcion){
			if(resultado < 0){
				casoError(descripcion);
			}else if(resultado == 0){
				casoSocketCerrado(descripcion);
			}else{
				casoExitoso(descripcion);
			}
		}

		void casoError(string descripcion){
			Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir informacion de: "+ descripcion +", se cierra el socket", to_string(errno));
			throw runtime_error(descripcion+" Error");
		};

		void casoSocketCerrado(string descripcion){
			Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de: "+ descripcion +", se cierra el socket");
			throw runtime_error(descripcion+" Error");

		};
		void casoExitoso(string descripcion){
			Log::getInstance()->mostrarAccion("Se recibio exitosamente informacion de: "+ descripcion);
		};


	protected:
		int socket;
};


#endif /* SRC_UTILS_ENVIADOR_HPP_ */
