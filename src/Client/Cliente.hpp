#ifndef SRC_CLIENT_CLIENTE_HPP_
#define SRC_CLIENT_CLIENTE_HPP_

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <queue>
#include <map>

#include "../Utils/Escuchador.hpp"
#include "../Utils/Utils.hpp"
#include "app/VentanaInicio/VentanaInicio.hpp"
#include "../Utils/Enviador.hpp"

class EscuchadorVerificacionCredenciales;
#include "../../src/Client/Escuchadores/EscuchadorVerificacionCredenciales.hpp"
class EscuchadorActualizacionJugadores;
#include "../../src/Client/Escuchadores/EscuchadorActualizacionJugadores.hpp"
class EscuchadorInfoPartidaInicial;
#include "../../src/Client/Escuchadores/EscuchadorInfoPartidaInicial.hpp"
class EscuchadorRonda;
#include "../../src/Client/Escuchadores/EscuchadorRonda.hpp"
#include "../../src/Client/Escuchadores/EscuchadorSonido.hpp"

#include "Escuchadores/EscuchadorLog.hpp"

class GameLoop;
#include "../Client/GameLoop.hpp"

using namespace std;
#define LARGO_IP 20

class Cliente{

	public:
		Cliente(char ip[LARGO_IP], int puerto);
		~Cliente();

		void enviar();
		void escuchar();
		void recibirVerificacionCredenciales(verificacion_t verificacion);
		void recibirInformacionActualizacion(actualizacion_cantidad_jugadores_t actualizacion);
		void recibirInformacionRonda(info_ronda_t info_ronda) const;
		void ejecutar();
		void agregarEntrada(entrada_usuario_t entradaUsuario);
		void empezarJuego(info_partida_t info_partida);

		static void* escuchar_helper(void* ptr){
			((Cliente*) ptr)->escuchar();
			return NULL;
		}
		static void* enviar_helper(void* ptr){
			((Cliente*) ptr)->enviar();
			return NULL;
		}

	private:
		void enviarCredenciales(credencial_t credencial);
		void esperarRecibirInformacionInicio() const;
		void esperarRecibirVerificacion() const;
		void terminarProcesosDelCliente();
		void cerradoVentanaInicio() const;
		void esperarAQueEmpieceElJuego();
		void intentarEntrarAlJuego();

		map<char,Enviador*> enviadores;
		map<char,Escuchador*> escuchadores;

		queue<char> identificadoresMensajeAEnviar;

		VentanaInicio* ventanaInicio;

		info_partida_t infoPartida{};
		verificacion_t pasoVerificacion;
		bool cargoLaAplicacion;
		bool seRecibioInformacionInicio;
		bool seRecibioVerificacion;
		bool empiezaElJuego;
		bool terminoJuego;
		bool cerroVentana;

		bool terminoEnviar;
		bool terminoEscuchar;

		int socketCliente;
		unsigned short cantidadJugadoresActivos;

		GameLoop* gameLoop;
};
#endif /* SRC_CLIENT_CLIENTE_HPP_ */
