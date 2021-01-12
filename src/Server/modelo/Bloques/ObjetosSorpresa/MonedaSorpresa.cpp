#include "MonedaSorpresa.hpp"

MonedaSorpresa::MonedaSorpresa() {
    usado = false;
}

void MonedaSorpresa::usarse(Mario *mario) {
    if(!usado){
        mario->agregarMoneda();
        usado = true;
    }
}
