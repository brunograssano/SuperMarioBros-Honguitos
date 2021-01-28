#ifndef SRC_SERVER_CONEXIONCLIENTE_HPP_
#define SRC_SERVER_CONEXIONCLIENTE_HPP_

class Servidor;

#include <thread>
#include <string>
#include <map>

#include "src/Utils/log/Log.hpp"
#include "src/Utils/Utils.hpp"
#include "src/Utils/Thread.hpp"

class EnviadorConexionCliente;
class EscuchadorConexionCliente;

class ConexionCliente : public Thread{

	public:
		ConexionCliente(Servidor *servidor, int socket, std::string ip,actualizacion_cantidad_jugadores_t informacionAMandar);
		~ConexionCliente() override;

		void ejecutar() override;
		void enviarActualizacionesDeRonda();
        void agregarMensajeAEnviar(char caracter, void *mensaje);

        void recibirCredencial(std::string nombre,std::string contrasenia);
		void agregarIDJuego(int IDJugador);
        std::string obtenerIP();
		void terminarElJuego();
        bool terminoElJuego() const;

        void desconectarse();

    private:
		actualizacion_cantidad_jugadores_t informacionAMandar{};
		void esperarCredenciales();

		EscuchadorConexionCliente* escuchador{};
        EnviadorConexionCliente* enviador{};

        std::string nombre;
        std::string contrasenia;

        bool terminoJuego;
		bool recibioCredenciales;

		int idPropio;
		int socket;
        std::string ip;
		Servidor* servidor;

};


#endif /* SRC_SERVER_CONEXIONCLIENTE_HPP_ */
