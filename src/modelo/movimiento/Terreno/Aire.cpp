#include "Aire.h"
float Aire::aplicarCoeficienteDeRozamiento(float velocidadX){
	if(velocidadX < 0)
		return (velocidadX + coeficienteDeRozamiento);
	else//(velocidadX > 0)
		return (velocidadX - coeficienteDeRozamiento);
}

float Aire::obtenerImpulsoHorizontal(float aceleracion){
	return aceleracion/2;	//Quito aceleracion por estar en el aire
	return 0;
}

float Aire::obtenerImpulsoVertical(float fuerza){
	return 0;
}
