#include "Escuchador.hpp"

void Escuchador::escuchar() {
    int resultado = socket->escuchar(structPointer, bytes);
    if(resultado < 0){
        casoError(resultado);
    }else if(resultado == 0){
        casoSocketCerrado();
    }else{
        casoExitoso();
    }
}
