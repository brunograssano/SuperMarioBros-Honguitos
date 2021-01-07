#ifndef SRC_SERVER_CONEXIONCLIENTE_HPP_
#define SRC_SERVER_CONEXIONCLIENTE_HPP_

class Servidor;
#include "Servidor.hpp"

using namespace std;
#include <thread>
#include <string>
#include <map>

#include "../Utils/log/Log.hpp"
#include "../Utils/Utils.hpp"

#include "EnviadoresServer/EnviadorConexionCliente.hpp"
class EscuchadorConexionCliente;
#include "EscuchadoresServer/EscuchadorConexionCliente.hpp"

class ConexionCliente {

	public:
		ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones,string ip, actualizacion_cantidad_jugadores_t informacionAMandar);
		~ConexionCliente();

        static void* ejecutar_helper(void* ptr);
        static void* enviar_helper(void* ptr);
		static void* escuchar_helper(void* ptr);
		void ejecutar();

		void enviarActualizacionesDeRonda() const;
        void agregarMensajeAEnviar(char caracter, void *mensaje);
		void actualizarCliente(actualizacion_cantidad_jugadores_t actualizacion);
		void recibirCredencial(string nombre,string contrasenia);
		void agregarIDJuego(int IDJugador);
		string obtenerIP();
        string obtenerNombre();
        string obtenerContrasenia();
		void terminoElJuego();


private:
		actualizacion_cantidad_jugadores_t informacionAMandar{};
		void esperarCredenciales();

		EscuchadorConexionCliente* escuchador;
        EnviadorConexionCliente* enviador;

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
};


#endif /* SRC_SERVER_CONEXIONCLIENTE_HPP_ */
