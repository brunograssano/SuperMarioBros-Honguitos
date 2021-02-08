#include "EnviadorPodio.hpp"

EnviadorPodio::EnviadorPodio(Socket* socket) {
    this->socket = socket;
    memset(&ultimos_podios,0,sizeof(ultimos_podios_t));
}

void EnviadorPodio::enviar() {
    Enviador::enviar(PODIO,&ultimos_podios,sizeof(ultimos_podios_t));
}

void EnviadorPodio::dejarInformacion(void *informacionPodio) {
    ultimos_podios =  *((ultimos_podios_t *) informacionPodio);
}