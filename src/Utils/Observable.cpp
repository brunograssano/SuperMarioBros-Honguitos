#include "Observable.hpp"
#include "Observador.hpp"

void Observable::agregar(Observador* observador){
    observadores.push_back(observador);
}
void Observable::eliminar(Observador* observador){
    observadores.remove(observador);
}
void Observable::notificar(){
    for(auto const& observador:observadores){
        observador->actualizar(this);
    }
}

