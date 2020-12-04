#ifndef SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_
#define SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_

#include "EscuchadorServer.hpp"
#include "../ConexionCliente.hpp"


class EscuchadorCredenciales: public EscuchadorServer{

	public:
		EscuchadorCredenciales(int socket,ConexionCliente* cliente){
			this->socket = socket;
			this->conexionCliente = cliente;
		}

		void escuchar()override{
			credencial_t credencial;
			pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
			string nombre;
			string contrasenia;

			int resultado = recv(socket, &credencial, sizeof(credencial_t), MSG_WAITALL);

			if(resultado<0){
				pthread_mutex_lock(&mutex);
				Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de las credenciales, se cierra el socket", to_string(errno));
				pthread_mutex_unlock(&mutex);
				throw runtime_error("ErrorAlRecibirCredenciales");
			}else if(resultado == 0){
				pthread_mutex_lock(&mutex);
				Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de las credenciales, se cierra el socket");
				pthread_mutex_unlock(&mutex);
				throw runtime_error("ErrorAlRecibirCredenciales");
			}

			nombre = string(credencial.nombre);
			contrasenia = string(credencial.contrasenia);

			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se recibieron las credenciales:" + nombre + " | " +contrasenia +" del cliente: " + conexionCliente->obtenerIP());
			pthread_mutex_unlock(&mutex);

			conexionCliente->recibirCredencial(nombre, contrasenia);
		}

	private:
		int socket;
		ConexionCliente* conexionCliente;

};



#endif /* SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_ */
