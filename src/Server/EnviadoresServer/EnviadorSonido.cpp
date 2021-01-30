#include "EnviadorSonido.hpp"
pthread_mutex_t mutexSonido = PTHREAD_MUTEX_INITIALIZER;

EnviadorSonido::EnviadorSonido(Socket* socket) {
    this->socket = socket;
}

void EnviadorSonido::enviar() {
    sonido_t sonido;
    memset(&sonido,0,sizeof(sonido_t));

    if(!colaSonidos.empty()){
        pthread_mutex_lock(&mutexSonido);
        sonido = colaSonidos.front();
        colaSonidos.pop();
        pthread_mutex_unlock(&mutexSonido);
        Enviador::enviar(SONIDO,&sonido,sizeof(sonido_t));
    }
}

void EnviadorSonido::dejarInformacion(void *sonido) {
    pthread_mutex_lock(&mutexSonido);
    colaSonidos.push(*((sonido_t*) sonido));
    pthread_mutex_unlock(&mutexSonido);
}
