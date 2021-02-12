#include "EnviadorSonido.hpp"

EnviadorSonido::EnviadorSonido(Socket* socket) {
    this->socket = socket;
}

void EnviadorSonido::enviar() {
    sonido_t sonido;
    memset(&sonido,0,sizeof(sonido_t));

    if(!colaSonidos.empty()){
        sonido = colaSonidos.front();
        colaSonidos.pop();
        Enviador::enviar(SONIDO,&sonido,sizeof(sonido_t));
    }
}

void EnviadorSonido::dejarInformacion(void *sonido) {
    colaSonidos.push(*((sonido_t*) sonido));
}
