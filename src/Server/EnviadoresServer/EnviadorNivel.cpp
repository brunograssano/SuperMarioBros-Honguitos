#include "EnviadorNivel.hpp"

EnviadorNivel::EnviadorNivel(int socket) {
    this->socket = socket;
    memset(&info_nivel,0,sizeof(nivel_t));
}

void EnviadorNivel::enviar() {
    char caracterMensaje = NIVEL;

    int resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
    this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de un nivel");

    resultadoEnvio = send(socket, &info_nivel , sizeof(nivel_t), 0);
    this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de un nivel");
}

void EnviadorNivel::dejarInformacion(void *informacionNivel) {
    info_nivel =  *((nivel_t*) informacionNivel);
}
