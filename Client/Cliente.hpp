#ifndef CLIENT_CLIENTE_HPP_
#define CLIENT_CLIENTE_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <queue>
#include <map>

#include "../src/Utils.hpp"

#include "Escuchadores/Escuchador.hpp"
class EscuchadorInformacionPartida;
#include "Escuchadores/EscuchadorInformacionPartida.hpp"
class EscuchadorVerificacionCredenciales;
#include "Escuchadores/EscuchadorVerificacionCredenciales.hpp"
class EscuchadorActualizacionJugadores;
#include "Escuchadores/EscuchadorActualizacionJugadores.hpp"

#include "Escuchadores/EscuchadorLog.hpp"

#include "../src/app/VentanaInicio/VentanaInicio.hpp"

#include "../src/Utils.hpp"

using namespace std;

#define LARGO_IP 20


class Cliente{

	public:
		Cliente(char ip[LARGO_IP], int puerto);
		~Cliente();
		void enviarEntrada();
		void escuchar();
		static void* escuchar_helper(void* ptr){
			((Cliente*) ptr)->escuchar();
			return NULL;
		}
		static void* enviar_helper(void* ptr){
			((Cliente*) ptr)->enviarEntrada();
			return NULL;
		}
		void recibirInformacionServidor(info_inicio_t info_inicio);
		void recibirVerificacionCredenciales(verificacion_t verificacion);
		void recibirInformacionActualizacionCantidadJugadores(unsigned short cantidadJugadores);
		void ejecutar();
		void agregarEntrada(entrada_usuario_t entradaUsuario);
	private:
		queue<entrada_usuario_t> entradasUsuario;
		map<char,Escuchador*> escuchadores;
		void enviarCredenciales(credencial_t credencial);

		unsigned short cantidadJugadoresActivos;

		bool seRecibioInformacionInicio = false;
		info_inicio_t infoInicio;
		void esperarRecibirInformacionInicio();

		bool seRecibioVerificacion = false;
		verificacion_t pasoVerificacion = false;
		void esperarRecibirVerificacion();

		bool empiezaElJuego = false;

		int socketCliente;
};
#endif /* CLIENT_CLIENTE_HPP_ */
