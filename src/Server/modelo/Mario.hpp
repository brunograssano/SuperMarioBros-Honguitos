#ifndef SRC_SERVER_MODELO_MARIO_HPP_
#define SRC_SERVER_MODELO_MARIO_HPP_

#include "movimiento/MovimientoMario.hpp"
#include "Posicion.hpp"

#include "../../Utils/Utils.hpp"

class SpriteMario;
#include "../sprites/SpriteMario.hpp"

class Mario{

	public:

		Mario(int numeroJugador);
		int obtenerPuntos();
		void agregarPuntos(int unosPuntos);
		int obtenerMonedas();
		void agregarMoneda();

		SpriteMario* obtenerSpite();
		int obtenerPosicionX();
		int obtenerPosicionY();
		bool estaConectado();
		bool estaQuietoX();
		bool estaEnElPiso();
		void actualizarPosicion();
		void reiniciarPosicion();
		
		void actualizarSaltarMario();
		void actualizarAgacharseMario();
		void actualizarIzquierdaMario();
		void actualizarDerechaMario();

		jugador_t serializar(char nombreJugador[MAX_NOMBRE], unsigned short idImagen);

		void serArrastrado(int corrimiento);
		void actualizarMaximoX(int limite);
		void actualizarMinimoX(int limite);
		~Mario();

	private:
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		SpriteMario * spriteMario;
		int puntos;
		int cantidadMonedas;
		int numeroJugador;
		bool estaConectadoElJugador;
};


#endif
