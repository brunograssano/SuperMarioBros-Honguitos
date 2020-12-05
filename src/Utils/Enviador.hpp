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
		virtual void enviar(){};
		virtual void dejarInformacion(void* informacion){};

		void revisarSiSeMandoCorrectamente(int resultado, string descripcion){
			if(resultado < 0){
				casoError(resultado, descripcion);
			}else if(resultado == 0){
				casoSocketCerrado(descripcion);
			}else{
				casoExitoso(descripcion);
			}
		}

		void casoError(int resultado, string descripcion){
			pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_lock(&mutex);
			Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir informacion de: "+ descripcion +", se cierra el socket", to_string(errno));
			pthread_mutex_unlock(&mutex);
			throw runtime_error(descripcion+" Error");
		};

		void casoSocketCerrado(string descripcion){
			pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de: "+ descripcion +", se cierra el socket");
			pthread_mutex_unlock(&mutex);
			throw runtime_error(descripcion+" Error");

		};
		void casoExitoso(string descripcion){
			pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarAccion("Se recibio exitosamente informacion de: "+ descripcion);
			pthread_mutex_unlock(&mutex);
		};


	protected:
		int socket;
};


#endif /* SRC_UTILS_ENVIADOR_HPP_ */
