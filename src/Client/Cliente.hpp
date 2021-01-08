#ifndef SRC_CLIENT_CLIENTE_HPP_
#define SRC_CLIENT_CLIENTE_HPP_

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <queue>
#include <map>

#include "../Utils/Utils.hpp"
#include "app/VentanaInicio/VentanaInicio.hpp"

class EnviadorCliente;
#include "../../src/Client/EnviadoresCliente/EnviadorCliente.hpp"

class EscuchadorCliente;
#include "../../src/Client/Escuchadores/EscuchadorCliente.hpp"

class GameLoop;
#include "../Client/GameLoop.hpp"

using namespace std;
#define LARGO_IP 20

class Cliente{

	public:
		Cliente(char ip[LARGO_IP], int puerto);
		~Cliente();

        void terminarProcesosDelCliente();
        void agregarMensajeAEnviar(char tipoMensaje, void *mensaje);
		void recibirVerificacionCredenciales(verificacion_t verificacion);
		void recibirInformacionActualizacion(actualizacion_cantidad_jugadores_t actualizacion);
		void recibirInformacionRonda(info_ronda_t info_ronda) const;
		void ejecutar();
		void empezarJuego(info_partida_t info_partida);

		static void* escuchar_helper(void* ptr);
		static void* enviar_helper(void* ptr);

    void recibirInformacionNivel(nivel_t nivel);

private:
        static void esperar(const bool *condicionAEsperar);
		void cerradoVentanaInicio() const;
		void esperarAQueEmpieceElJuego();
		void intentarEntrarAlJuego();

		EscuchadorCliente* escuchador{};
        EnviadorCliente* enviador{};
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