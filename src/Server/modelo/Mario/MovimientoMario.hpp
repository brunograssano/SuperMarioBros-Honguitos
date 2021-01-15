#ifndef SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_HPP_
#define SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_HPP_

#include "src/Server/modelo/movimiento/MovimientoHorizontal.hpp"
#include "src/Server/modelo/movimiento/MovimientoVertical.hpp"
#include "src/Server/modelo/Terreno/Aire.hpp"
#include "src/Server/modelo/Terreno/Tierra.hpp"
#include "src/Server/modelo/Posicion.hpp"
#include "src/Server/modelo/Terreno/Terreno.hpp"
#include <map>

class MovimientoMario{
	public:
		MovimientoMario();
		~MovimientoMario();
		void aceleraraDerecha();
		void aceleraraIzquierda();
		bool estaQuieto();
		void saltar();
		void setVelocidadY(int velocidad);
        float obtenerVelocidadXActual();
		void mover(PosicionMovil* posicion);
        void impulsarY();
        void reiniciar();
        void setVelocidadX(int velocidadNueva);
        void teParasteEnBloque();
        bool estaEnElAire() const;

    private:
		MovimientoHorizontal movimientoX = MovimientoHorizontal(0, 0);
		MovimientoVertical movimientoY = MovimientoVertical(0);
		std::map<int,Terreno*> terrenos;
		int terrenoActual;
};


#endif /* SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_HPP_ */
