#ifndef SRC_SERVER_CONEXIONCLIENTE_HPP_
#define SRC_SERVER_CONEXIONCLIENTE_HPP_

class Servidor;

using namespace std;
#include <thread>
#include <string>
#include <map>

#include "../Utils/log/Log.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Thread.hpp"

class EnviadorConexionCliente;
class EscuchadorConexionCliente;

class ConexionCliente : public Thread{

	public:
		ConexionCliente(Servidor *servidor, int socket, string ip,actualizacion_cantidad_jugadores_t informacionAMandar);
		~ConexionCliente() override;

		void ejecutar() override;
		void enviarActualizacionesDeRonda();
        void agregarMensajeAEnviar(char caracter, void *mensaje);

        void recibirCredencial(string nombre,string contrasenia);
		void agregarIDJuego(int IDJugador);
		string obtenerIP();
		void terminarElJuego();
        bool terminoElJuego() const;

        void desconectarse();

private:
		actualizacion_cantidad_jugadores_t informacionAMandar{};
		void esperarCredenciales();

		EscuchadorConexionCliente* escuchador{};
        EnviadorConexionCliente* enviador{};

		string nombre;
		string contrasenia;

        bool terminoJuego;
		bool recibioCredenciales;

		int idPropio;
		int socket;
		string ip;
		Servidor* servidor;

};


#endif /* SRC_SERVER_CONEXIONCLIENTE_HPP_ */
