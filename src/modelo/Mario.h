#ifndef SRC_MODELO_MARIO_H_
#define SRC_MODELO_MARIO_H_

#include "../modelo/Posicion.h"
#include "../modelo/movimiento/MovimientoMario.h"

class SpriteMario;
#include "../sprites/SpriteMario.h"

class Mario{

	public:

		Mario();
		int obtenerPuntos();
		void agregarPuntos(int unosPuntos);
		int obtenerMonedas();
		void agregarMoneda();

		SpriteMario* obtenerSpite();
		int obtenerPosicionX();
		int obtenerPosicionY();
		void aceleraraIzquierda();
		void aceleraraDerecha();
		void saltar();
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
};


#endif
