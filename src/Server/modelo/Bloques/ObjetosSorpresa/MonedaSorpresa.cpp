#include "MonedaSorpresa.h"

MonedaSorpresa::MonedaSorpresa() {
    usado = false;
}

void MonedaSorpresa::usarse(Mario *mario) {
    mario->agregarMoneda();//habria que asegurarse que el que obtiene la moneda es el que choco el bloque
    usado = true;
}
