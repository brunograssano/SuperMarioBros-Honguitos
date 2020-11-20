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
#include <map>

#include "../src/Utils.hpp"

#include "EscuchadorSalaDeEspera.hpp"

#include "Escuchadores/Escuchador.hpp"
class EscuchadorInformacionPartida;
#include "Escuchadores/EscuchadorInformacionPartida.hpp"
class EscuchadorVerificacionCredenciales;
#include "Escuchadores/EscuchadorVerificacionCredenciales.hpp"
#include "../src/app/VentanaInicio/VentanaInicio.hpp"

using namespace std;

const int LARGO_IP = 20;


class Cliente{

	public:
		Cliente(char ip[LARGO_IP], int puerto);
		~Cliente();
		void enviar();
		void escuchar();
		static void* escuchar_helper(void* ptr){
			((Cliente*) ptr)->escuchar();
			return NULL;
		}
		static void* enviar_helper(void* ptr){
			((Cliente*) ptr)->enviar();
			return NULL;
		}
		void recibirInformacionServidor(info_inicio_t info_inicio);
		void recibirVerificacionCredenciales(verificacion_t verificacion);
		void ejecutar();

	private:
		info_estado_actual_partida_t infoEstadoPartida = {0};
		map<char,Escuchador*> escuchadores;
		void enviarCredenciales(credencial_t credencial);

		bool seRecibioInformacionInicio = false;
		info_inicio_t infoInicio;
		void esperarRecibirInformacionInicio();

		bool seRecibioVerificacion = false;
		verificacion_t pasoVerificacion = false;
		void esperarRecibirVerificacion();

		int socketCliente;
};
#endif /* CLIENT_CLIENTE_HPP_ */
