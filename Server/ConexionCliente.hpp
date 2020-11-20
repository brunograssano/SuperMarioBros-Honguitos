#ifndef SERVER_CONEXIONCLIENTE_HPP_
#define SERVER_CONEXIONCLIENTE_HPP_

class Servidor;
#include "Servidor.hpp"

using namespace std;
#include <thread>
#include <string>

#include "../src/Utils.hpp"

#include "../src/log/Log.hpp"

class ConexionCliente {

	public:
		ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones);
		~ConexionCliente();

		void recibir();
		void ejecutar();
		static void* ejecutar_helper(void* ptr){
			((ConexionCliente*) ptr)->ejecutar();
			return NULL;
		}
		void actualizarCantidadConexiones(int cantidadConexiones);
		void enviar(char* msg);


	private:
		info_inicio_t crearInformacionInicio();
		void enviarInformacionInicio();
		string nombre;
		string contrasenia;
		int socket;
		Servidor* servidor;
		int cantidadConexiones;
		void recibirCredenciales();
};


#endif /* SERVER_CONEXIONCLIENTE_HPP_ */
