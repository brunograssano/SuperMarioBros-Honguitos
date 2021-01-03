#ifndef SRC_SERVER_MODELO_MARIO_HPP_
#define SRC_SERVER_MODELO_MARIO_HPP_


#include "src/Server/modelo/Posicion.hpp"
#include "src/Utils/log/Log.hpp"
#include "src/Utils/Utils.hpp"

#include "MovimientoMario.hpp"
#include "VidaMario.h"
#include "Modificadores/ModificadorMario.h"
#include "Modificadores/SinModificador.h"
#include "Modificadores/MarioDeFuego.h"

class SpriteMario;
#include "src/Server/sprites/SpriteMario.hpp"

class Mario{

	public:

		Mario(int numeroJugador);
		int obtenerPuntos() const;
		void agregarPuntos(int unosPuntos);
		int obtenerMonedas() const;
		void agregarMoneda();

		SpriteMario* obtenerSpite();
		int obtenerPosicionX();
		int obtenerPosicionY();
		bool estaConectado() const;
		bool estaQuietoX();
		bool estaEnElPiso();
		void actualizarPosicion();
		void reiniciarPosicion();
		
		void actualizarSaltarMario();
		void actualizarAgacharseMario();
		void actualizarIzquierdaMario();
		void actualizarDerechaMario();

        void perderVida();
        void hacerseDeFuego();
        void dispararFuego();//agregarle lo que se necesite

		jugador_t serializar(const char nombreJugador[MAX_NOMBRE], unsigned short idImagen);
		void desconectar(){
			estaConectadoElJugador = false;
		}
		void conectar(){
			estaConectadoElJugador = true;
		}
		void serArrastrado(int corrimiento);
		void actualizarMaximoX(int limite);
		void actualizarMinimoX(int limite);
		~Mario();

	private:
        void swapDeModificador(ModificadorMario *nuevoModificador);
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		SpriteMario * spriteMario;
		ModificadorMario* modificador;
		VidaMario* vidaMario;
		int puntos;
		int numeroJugador;
		bool estaConectadoElJugador;
};


#endif
