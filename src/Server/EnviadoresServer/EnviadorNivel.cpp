#include "EnviadorNivel.hpp"

EnviadorNivel::EnviadorNivel(Socket* socket) {
    this->socket = socket;
    memset(&info_nivel,0,sizeof(nivel_t));
}

void EnviadorNivel::enviar() {
    Enviador::enviar(NIVEL,&info_nivel,sizeof(nivel_t));
}

void EnviadorNivel::dejarInformacion(void *informacionNivel) {
    info_nivel =  *((nivel_t*) informacionNivel);
}
