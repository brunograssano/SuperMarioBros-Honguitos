#ifndef CLIENT_ESCUCHADORES_ESCUCHADORLOG_HPP_
#define CLIENT_ESCUCHADORES_ESCUCHADORLOG_HPP_
#include <thread>

#include <string>
using namespace std;

#include "../../src/log/Log.hpp"

#include "Escuchador.hpp"

class EscuchadorLog : public Escuchador{

	public:

		EscuchadorLog(int socket){
			this->socket = socket;
		}

		void escuchar()override{
			mensaje_log_t conjuntoMensajeLog;
			strcpy(conjuntoMensajeLog.mensajeParaElLog,"");
			conjuntoMensajeLog.tipo = ' ';
			int resultado;
			pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

			resultado = recv(socket, &conjuntoMensajeLog, sizeof(mensaje_log_t), MSG_WAITALL);
			if(resultado < 0){
				pthread_mutex_lock(&mutex);
				Log::getInstance()->huboUnErrorSDL("Ocurrio un error al recibir un mensaje del log",to_string(errno));
				pthread_mutex_unlock(&mutex);
				//LANZAR EXCEPCION?
			}

			string mensajeLog(conjuntoMensajeLog.mensajeParaElLog);
			if(conjuntoMensajeLog.tipo == TIPO_ERROR){
				pthread_mutex_lock(&mutex);
				Log::getInstance()->huboUnError(mensajeLog);
				pthread_mutex_unlock(&mutex);
			}
			else if(conjuntoMensajeLog.tipo == INFO){
				pthread_mutex_lock(&mutex);
				Log::getInstance()->mostrarMensajeDeInfo(mensajeLog);
				pthread_mutex_unlock(&mutex);
			}
		}

	private:
		int socket;

};



#endif /* CLIENT_ESCUCHADORES_ESCUCHADORLOG_HPP_ */
