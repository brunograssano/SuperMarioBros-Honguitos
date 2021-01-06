#ifndef SRC_SERVER_CONEXIONCLIENTE_HPP_
#define SRC_SERVER_CONEXIONCLIENTE_HPP_

class Servidor;
#include "Servidor.hpp"

using namespace std;
#include <thread>
#include <string>
#include <map>

#include "../Utils/Enviador.hpp"
#include "../Utils/log/Log.hpp"
#include "../Utils/Escuchador.hpp"
#include "../Utils/Utils.hpp"
class EscuchadorEntradaTeclado;
#include "EscuchadoresServer/EscuchadorEntradaTeclado.hpp"

class ConexionCliente {

	public:
		ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones,string ip, actualizacion_cantidad_jugadores_t informacionAMandar);
		~ConexionCliente();

		void escuchar();
		static void* escuchar_helper(void* ptr){
			((ConexionCliente*)ptr)->escuchar();
			return NULL;
		}

		void ejecutar();
		static void* ejecutar_helper(void* ptr){
			((ConexionCliente*) ptr)->ejecutar();
			return NULL;
		}


		void enviar();
		static void* enviar_helper(void* ptr){
			((ConexionCliente*) ptr)->enviar();
			return NULL;
		}

		void enviarActualizacionesDeRonda() const;
        void agregarMensajeAEnviar(char caracter, void *mensaje);
		void actualizarCliente(actualizacion_cantidad_jugadores_t actualizacion);
		void recibirCredencial(string nombre,string contrasenia);
		void agregarIDJuego(int IDJugador);
		string obtenerIP(){
			return ip;
		}

		void terminoElJuego();

	private:
		actualizacion_cantidad_jugadores_t informacionAMandar{};
		void esperarCredenciales();

		queue<char> identificadoresMensajeAEnviar;

		string nombre;
		string contrasenia;

		bool puedeJugar;
		bool terminoJuego;
		bool recibioCredenciales;

		int idPropio;
		int socket;
		int cantidadConexiones;
		string ip;

		Servidor* servidor;
		map<char,Escuchador*> escuchadores;
		map<char,Enviador*> enviadores;
};


#endif /* SRC_SERVER_CONEXIONCLIENTE_HPP_ */
