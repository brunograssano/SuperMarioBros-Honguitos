#ifndef SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_
#define SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_

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
			int resultado = recv(socket,&credencial,sizeof(credencial_t),MSG_WAITALL);
			if(resultado<0){
				//todo
			}
			string nombre(credencial.nombre);
			string contrasenia(credencial.contrasenia);
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se recibieron las credenciales:" + nombre + " | " +contrasenia +" del cliente: " + "OBTENER IP!!!!!!!!!!!!!!!!!");
			pthread_mutex_unlock(&mutex);
			conexionCliente->recibirCredencial(nombre,contrasenia);
		}

	private:
		int socket;
		ConexionCliente* conexionCliente;

};



#endif /* SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_ */
