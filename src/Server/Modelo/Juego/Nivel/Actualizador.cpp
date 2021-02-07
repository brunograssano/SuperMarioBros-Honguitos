
#include "Actualizador.hpp"

void Actualizador::actualizar(std::list<Moneda *> *actualizables) {
    for(auto& moneda : *actualizables){
        moneda->actualizar();
    }
    sacarMonedasAgarradas(actualizables);
}

void Actualizador::actualizar(std::list<ObjetoFugaz *> *actualizables) {
    for(auto& objetoFugaz : *actualizables){
        objetoFugaz->actualizar();
    }
    sacarObjetosFugaces(actualizables);
}

void Actualizador::actualizar(std::list<Bloque *> *actualizables) {
    for(auto& bloque : *actualizables){
        bloque->actualizar();
    }
}

void Actualizador::sacarMonedasAgarradas(std::list<Moneda*> *monedas) {
    std::list<Moneda*> monedasABorrar;
    for(auto moneda : *monedas){
        if(moneda->fueAgarrada()){
            monedasABorrar.push_back(moneda);
        }
    }
    for(auto moneda : monedasABorrar ){
        monedas->remove(moneda);
        delete moneda;
    }
}

void Actualizador::sacarObjetosFugaces(std::list<ObjetoFugaz*> *objetosFugaces) {
    std::list<ObjetoFugaz*> objetosABorrar;
    for(auto objeto: *objetosFugaces){
        if(objeto->debeDesaparecer()){
            objetosABorrar.push_back(objeto);
        }
    }
    for(auto objeto : objetosABorrar){
        objetosFugaces->remove(objeto);
        delete objeto;
    }
}