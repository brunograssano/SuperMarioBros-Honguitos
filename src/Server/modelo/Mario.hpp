#ifndef SRC_SERVER_MODELO_MARIO_HPP_
#define SRC_SERVER_MODELO_MARIO_HPP_

#include "movimiento/MovimientoMario.hpp"
#include "Posicion.hpp"

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
		bool estaQuietoX();
		bool estaEnElPiso();
		void actualizarPosicion();
		void reiniciarPosicion();
		
		void actualizarSaltarMario();
		void actualizarAgacharseMario();
		void actualizarIzquierdaMario();
		void actualizarDerechaMario();

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
};


#endif
