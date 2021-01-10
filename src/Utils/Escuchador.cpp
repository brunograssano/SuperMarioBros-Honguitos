#include "Escuchador.hpp"

void Escuchador::escuchar() {
    int resultado = recv(socket, structPointer, bytes, MSG_WAITALL);
    if(resultado < 0){
        casoError(resultado);
    }else if(resultado == 0){
        casoSocketCerrado();
    }else{
        casoExitoso();
    }
}
