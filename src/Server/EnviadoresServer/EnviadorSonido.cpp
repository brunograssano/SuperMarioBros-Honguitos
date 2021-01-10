#include "EnviadorSonido.hpp"

EnviadorSonido::EnviadorSonido(int socket) {
    this->socket = socket;
}

void EnviadorSonido::enviar() {
    sonido_t sonido;
    memset(&sonido,0,sizeof(sonido_t));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    if(!colaSonidos.empty()){
        pthread_mutex_lock(&mutex);
        sonido = colaSonidos.front();
        colaSonidos.pop();
        pthread_mutex_unlock(&mutex);
        Enviador::enviar(SONIDO,&sonido,sizeof(sonido_t));
    }
}

void EnviadorSonido::dejarInformacion(void *sonido) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    colaSonidos.push(*((sonido_t*) sonido));
    pthread_mutex_unlock(&mutex);
}
