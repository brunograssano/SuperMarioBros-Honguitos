#include "Vacio.hpp"

float Vacio::aplicarCoeficienteDeRozamiento(float velocidadX) {
    return velocidadX;
}

float Vacio::obtenerImpulsoHorizontal(float aceleracion) {
    return 0;
}

float Vacio::obtenerImpulsoVertical(float fuerza) {
    return 0;
}

float Vacio::amortiguarVelocidad(float velocidadY) {
    return velocidadY;
}
