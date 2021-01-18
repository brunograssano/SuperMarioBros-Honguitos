#include "CabezaEnemigo.hpp"

CabezaEnemigo::CabezaEnemigo() {
    coeficienteDeRozamiento = 0.2;
}

float CabezaEnemigo::aplicarCoeficienteDeRozamiento(float velocidadX){
    if(velocidadX < 0)
        return (velocidadX + coeficienteDeRozamiento);
    else//(velocidadX > 0)
        return (velocidadX - coeficienteDeRozamiento);
}

float CabezaEnemigo::obtenerImpulsoHorizontal(float aceleracion){
    return aceleracion;		//El impulso será equivalente a la aceleracion por ser tierra.
}

float CabezaEnemigo::obtenerImpulsoVertical(float fuerza){
    return fuerza/2;
}

float CabezaEnemigo::amortiguarVelocidad(float velocidadY) {
    return 0;
}
