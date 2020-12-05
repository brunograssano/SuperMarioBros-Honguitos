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
		ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones,string ip);
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

		void recibirInformacionRonda(info_ronda_t info_ronda);
		void enviarActualizacionesDeRonda();

		void actualizarCliente(actualizacion_cantidad_jugadores_t actualizacion);
		void recibirCredencial(string nombre,string contrasenia);
		void agregarIDJuego(int IDJugador);
		void enviarInfoPartida(info_partida_t info_partida);
		void enviarMensajeLog(mensaje_log_t mensaje);
		string obtenerIP(){
			return ip;
		}

		void terminoElJuego();

	private:
		info_inicio_t crearInformacionInicio();
		void enviarInformacionInicio();
		void enviarVerificacion(bool esUsuarioValido);
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
