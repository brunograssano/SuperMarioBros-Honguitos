#include <stdexcept>
#include "src/Utils/log/Log.hpp"
#include "Enviador.hpp"


void Enviador::revisarSiSeMandoCorrectamente(int resultado, const std::string& descripcion) {
    if(resultado < 0){
        casoError(descripcion);
    }else if(resultado == 0){
        casoSocketCerrado(descripcion);
    }else{
        casoExitoso(descripcion);
    }
}

void Enviador::casoError(const std::string& descripcion) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir informacion de: "+ descripcion +", se cierra el socket", std::to_string(errno));
    throw std::runtime_error(descripcion+" Error");
}

void Enviador::casoSocketCerrado(const std::string& descripcion) {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de: "+ descripcion +", se cierra el socket");
    throw std::runtime_error(descripcion+" Error");

}

void Enviador::casoExitoso(const std::string& descripcion) {
    Log::getInstance()->mostrarAccion("Se recibio exitosamente informacion de: "+ descripcion);
}

void Enviador::enviar(char caracter,void *structPointer, unsigned int bytes) {
    int resultadoEnvio = socket->enviar(&caracter, sizeof(caracter));
    this->revisarSiSeMandoCorrectamente(resultadoEnvio, &"el caracter de mensaje " [ caracter]);

    resultadoEnvio = socket->enviar(structPointer, bytes);
    this->revisarSiSeMandoCorrectamente(resultadoEnvio, &"la informacion del mensaje " [ caracter]);
}
