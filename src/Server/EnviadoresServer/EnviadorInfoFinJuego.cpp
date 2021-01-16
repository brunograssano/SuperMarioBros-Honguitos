
#include "EnviadorInfoFinJuego.hpp"

EnviadorInfoFinJuego::EnviadorInfoFinJuego(int socket) {
    this->socket = socket;
    memset(&infoFinJuego,0,sizeof(info_fin_juego_t));
}

void EnviadorInfoFinJuego::enviar() {
    Enviador::enviar(INFO_FIN_JUEGO, &infoFinJuego, sizeof(info_fin_juego_t));
}

void EnviadorInfoFinJuego::dejarInformacion(void* infoFinJuego){
    this->infoFinJuego =  *((info_fin_juego_t *) infoFinJuego);
}