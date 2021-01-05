#include "EnviadorSonido.hpp"

EnviadorSonido::EnviadorSonido(int socket) {
    this->socket = socket;
}

void EnviadorSonido::enviar() {
    char caracterMensaje = SONIDO;
    sonido_t sonido;
    memset(&sonido,0,sizeof(sonido_t));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int resultadoEnvio = 0;;

    if(!colaSonidos.empty()){
        pthread_mutex_lock(&mutex);
        sonido = colaSonidos.front();
        colaSonidos.pop();
        pthread_mutex_unlock(&mutex);
        resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
        this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de mensaje de nombre");
        resultadoEnvio = send(socket, &sonido, sizeof(sonido_t), 0);
        this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de informacion de un nombre");
    }
}

void EnviadorSonido::dejarInformacion(void *sonido) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    colaSonidos.push(*((sonido_t*) sonido));
    pthread_mutex_unlock(&mutex);
}
