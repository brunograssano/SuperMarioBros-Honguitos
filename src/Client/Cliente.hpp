#ifndef SRC_CLIENT_CLIENTE_HPP_
#define SRC_CLIENT_CLIENTE_HPP_

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

#include "../../src/Client/Escuchadores/Escuchador.hpp"
#include "../Utils/Utils.hpp"

class EscuchadorInformacionPartida;
#include "../../src/Client/Escuchadores/EscuchadorInformacionPartida.hpp"
class EscuchadorVerificacionCredenciales;
#include "../../src/Client/Escuchadores/EscuchadorVerificacionCredenciales.hpp"
class EscuchadorActualizacionJugadores;
#include "../../src/Client/Escuchadores/EscuchadorActualizacionJugadores.hpp"
class EscuchadorInfoPartidaInicial;
#include "../../src/Client/Escuchadores/EscuchadorInfoPartidaInicial.hpp"


#include "Escuchadores/EscuchadorLog.hpp"

#include "app/VentanaInicio/VentanaInicio.hpp"

#include "../Utils/Utils.hpp"

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
		void empezarJuego(info_partida_t info_partida);
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

		void esperarCargaDeAplicacion();
		bool seCargoLaAplicacion = false;

		bool empiezaElJuego = false;

		int socketCliente;
};
#endif /* SRC_CLIENT_CLIENTE_HPP_ */
