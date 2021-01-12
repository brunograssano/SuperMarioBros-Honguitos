#ifndef SRC_MODELO_MOVIMIENTO_TERRENO_AIRE_H_
#define SRC_MODELO_MOVIMIENTO_TERRENO_AIRE_H_

#include "Terreno.hpp"

class Aire : public Terreno{

	public:
		Aire(){
			coeficienteDeRozamiento = 0.08;
		}

		~Aire(){
		}

		float aplicarCoeficienteDeRozamiento(float velocidadX) override;
		float obtenerImpulsoHorizontal(float aceleracion) override;
		float obtenerImpulsoVertical(float fuerza) override;
		float amortiguarVelocidad(float velocidadY) override;
	private:
		float coeficienteDeRozamiento;

};




#endif /* SRC_MODELO_MOVIMIENTO_TERRENO_AIRE_H_ */
