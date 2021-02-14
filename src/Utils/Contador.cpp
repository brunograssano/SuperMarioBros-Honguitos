#include "Contador.hpp"

Contador::Contador(int tiempo, int unidad) {
    tiempoTotal = tiempo;
    tiempoInicio = time(nullptr);
    this->unidad = unidad;
}

void Contador::iniciar() {
    tiempoInicio = time(nullptr);
}

int Contador::tiempoRestante() const {
    time_t tiempoActual = time(nullptr);
    double tiempoDesdeElComienzoEnSegundos = difftime(tiempoActual, tiempoInicio);
    int tiempoDesdeElComienzo = (int) tiempoDesdeElComienzoEnSegundos*unidad;
    if(tiempoDesdeElComienzo >= tiempoTotal){
        return 0;
    }else{
        return (tiempoTotal - tiempoDesdeElComienzo);
    }
}