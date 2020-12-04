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

#include "../Utils/Escuchador.hpp"
#include "../Utils/Utils.hpp"

class EscuchadorInformacionPartida;
#include "../../src/Client/Escuchadores/EscuchadorInformacionPartida.hpp"
class EscuchadorVerificacionCredenciales;
#include "../../src/Client/Escuchadores/EscuchadorVerificacionCredenciales.hpp"
class EscuchadorActualizacionJugadores;
#include "../../src/Client/Escuchadores/EscuchadorActualizacionJugadores.hpp"
class EscuchadorInfoPartidaInicial;
#include "../../src/Client/Escuchadores/EscuchadorInfoPartidaInicial.hpp"
class EscuchadorRonda;
#include "../../src/Client/Escuchadores/EscuchadorRonda.hpp"

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
		void recibirInformacionServidor(info_inicio_t info_inicio);
		void recibirVerificacionCredenciales(verificacion_t verificacion);
		void recibirInformacionActualizacionCantidadJugadores(unsigned short cantidadJugadores);
		void recibirInformacionRonda(info_ronda_t info_ronda);
		void ejecutar();
		void agregarEntrada(entrada_usuario_t entradaUsuario);
		void empezarJuego(info_partida_t info_partida);

		static void* escuchar_helper(void* ptr){
			((Cliente*) ptr)->escuchar();
			return NULL;
		}
		static void* enviar_helper(void* ptr){
			((Cliente*) ptr)->enviarEntrada();
			return NULL;
		}

	private:
		void enviarCredenciales(credencial_t credencial);
		void esperarRecibirInformacionInicio();
		void esperarRecibirVerificacion();

		queue<entrada_usuario_t> entradasUsuario;
		map<char,Escuchador*> escuchadores;

		info_partida_t infoPartida;
		info_inicio_t infoInicio;
		verificacion_t pasoVerificacion;
		bool cargoLaAplicacion;
		bool seRecibioInformacionInicio;
		bool seRecibioVerificacion;
		bool empiezaElJuego;
		bool terminoJuego;

		int socketCliente;
		unsigned short cantidadJugadoresActivos;
};
#endif /* SRC_CLIENT_CLIENTE_HPP_ */
