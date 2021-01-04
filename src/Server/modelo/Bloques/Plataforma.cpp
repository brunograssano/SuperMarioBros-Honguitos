#include "Plataforma.hpp"

void Plataforma::agregarBloque(Bloque *bloque) {
    bloques.push_back(bloque);
}

list<Bloque *> Plataforma::obtenerBloques() {
    return this->bloques;
}

list<bloque_t> Plataforma::serializarPlataforma() {
    list<bloque_t> bloquesSerializados;
    for(auto const& bloque: bloques){
        bloquesSerializados.push_back(bloque->serializar());
    }
    return bloquesSerializados;
}

Plataforma::~Plataforma() {
    for(auto const& bloque:bloques){
        delete bloque;
    }
    bloques.clear();
}
