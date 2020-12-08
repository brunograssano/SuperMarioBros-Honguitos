#include "Tierra.hpp"

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
