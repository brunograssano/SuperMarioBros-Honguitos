#include "src/Client/reproductorDeMusica/ReproductorMusica.hpp"
#include "src/Utils/log/Log.hpp"
#include "EscuchadorSonido.hpp"

EscuchadorSonido::EscuchadorSonido(int socketCliente) {
    this->socket = socket;
    structPointer = &this->sonido;
    bytes = sizeof(sonido_t);
    error = string("");
}

void EscuchadorSonido::casoError(int resultado) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de un nombre, se cierra el socket", to_string(errno));
    throw runtime_error("ErrorAlEscucharInformacionDeUnSonido");
}

void EscuchadorSonido::casoSocketCerrado() {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de un nombre, se cierra el socket");
    throw runtime_error("ErrorAlEscucharInformacionDeUnSonido");
}

void EscuchadorSonido::casoExitoso() {
    if(!recibioMensajeValido()){
        Log::getInstance()->huboUnError("Se desecho el mensaje recibido del servidor debido que: " + error);
        return;
    }else{
        ReproductorMusica::getInstance()->reproducirSonido(sonido.nombre);
    }
}

bool EscuchadorSonido::recibioMensajeValido() {
    bool ocurrioError = false;
    string nombreSonido = string(sonido.nombre);
    if(nombreSonido.empty()){
        error = string("El nombre esta vacio");
        ocurrioError = true;
    }//Revisar que sea alguno de los validos
    return !ocurrioError;
}
