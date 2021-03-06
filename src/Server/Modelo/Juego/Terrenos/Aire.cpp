#include "Aire.hpp"

Aire::Aire() {
    coeficienteDeRozamiento = 0.08;
}

float Aire::aplicarCoeficienteDeRozamiento(float velocidadX){
	if(velocidadX < 0)
		return (velocidadX + coeficienteDeRozamiento);
	else//(velocidadX > 0)
		return (velocidadX - coeficienteDeRozamiento);
}

float Aire::obtenerImpulsoHorizontal(float aceleracion){
	return (float)(aceleracion/1.5);	//Quito aceleracion por estar en el aire
}

float Aire::obtenerImpulsoVertical(float fuerza){
	return 0;
}

float Aire::amortiguarVelocidad(float velocidadY) {
    return velocidadY;
}
