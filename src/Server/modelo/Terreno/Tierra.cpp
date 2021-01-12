#include "Tierra.hpp"

Tierra::Tierra() {
    coeficienteDeRozamiento = 0.2;
}

float Tierra::aplicarCoeficienteDeRozamiento(float velocidadX){
	if(velocidadX < 0)
		return (velocidadX + coeficienteDeRozamiento);
	else//(velocidadX > 0)
		return (velocidadX - coeficienteDeRozamiento);
}

float Tierra::obtenerImpulsoHorizontal(float aceleracion){
	return aceleracion;		//El impulso será equivalente a la aceleracion por ser tierra.
}

float Tierra::obtenerImpulsoVertical(float fuerza){
	return fuerza;
}

float Tierra::amortiguarVelocidad(float velocidadY) {
    return 0;
}
