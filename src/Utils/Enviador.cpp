#include "Enviador.hpp"
#include <sys/socket.h>
#include "../Utils/log/Log.hpp"

void Enviador::revisarSiSeMandoCorrectamente(int resultado, const string& descripcion) {
    if(resultado < 0){
        casoError(descripcion);
    }else if(resultado == 0){
        casoSocketCerrado(descripcion);
    }else{
        casoExitoso(descripcion);
    }
}

void Enviador::casoError(const string& descripcion) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir informacion de: "+ descripcion +", se cierra el socket", to_string(errno));
    throw runtime_error(descripcion+" Error");
}

void Enviador::casoSocketCerrado(const string& descripcion) {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de: "+ descripcion +", se cierra el socket");
    throw runtime_error(descripcion+" Error");

}

void Enviador::casoExitoso(const string& descripcion) {
    Log::getInstance()->mostrarAccion("Se recibio exitosamente informacion de: "+ descripcion);
}

void Enviador::enviar(char caracter,const void *structPointer, unsigned int bytes) {
    int resultadoEnvio = send(socket, &caracter, sizeof(caracter), 0);
    this->revisarSiSeMandoCorrectamente(resultadoEnvio, &"el caracter de mensaje " [ caracter]);

    resultadoEnvio = send(socket, structPointer, bytes, 0);
    this->revisarSiSeMandoCorrectamente(resultadoEnvio, &"la informacion del mensaje " [ caracter]);
}
