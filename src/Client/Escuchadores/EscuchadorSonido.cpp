#include "src/Client/reproductorDeMusica/ReproductorMusica.hpp"
#include "src/Utils/log/Log.hpp"
#include "EscuchadorSonido.hpp"
#include "src/Utils/Constantes.hpp"

EscuchadorSonido::EscuchadorSonido(int socketCliente) {
    this->socket = socketCliente;
    structPointer = &this->sonido;
    bytes = sizeof(sonido_t);
    error = string("");
}

void EscuchadorSonido::casoError(int resultado) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de un sonido, se cierra el socket", to_string(errno));
    throw runtime_error("ErrorAlEscucharInformacionDeUnSonido");
}

void EscuchadorSonido::casoSocketCerrado() {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de un sonido, se cierra el socket");
    throw runtime_error("ErrorAlEscucharInformacionDeUnSonido");
}

void EscuchadorSonido::casoExitoso() {
    if(!recibioMensajeValido()){
        Log::getInstance()->huboUnError("Se desecho el mensaje recibido del servidor debido que: " + error);
        return;
    }else{
        ReproductorMusica::getInstance()->reproducirSonido(sonido.tipoSonido);
    }
}

bool EscuchadorSonido::recibioMensajeValido() {
    bool ocurrioError = false;
    if(!sonidoValido(sonido.tipoSonido)){
        error = string("el sonido es inválido.");
        ocurrioError = true;
    }
    return !ocurrioError;
}

bool EscuchadorSonido::sonidoValido(uint8_t tipo) {
    if(
        tipo == SONIDO_SALTO            || tipo == SONIDO_AGARRAR_MONEDA        ||
        tipo == SONIDO_MATAR_GOOMBA     || tipo == SONIDO_MATAR_KOOPA           ||
        tipo == SONIDO_APARECE_FLOR     || tipo == SONIDO_AGARRA_POWERUP        ||
        tipo == SONIDO_MORIR            || tipo == SONIDO_LANZAR_BOLA_DE_FUEGO  ||
        tipo == SONIDO_LANZAR_CHISPA    || tipo == SONIDO_REBOTE_BOLA_DE_FUEGO  ||
        tipo == SONIDO_EXPLOSION_BOLA_DE_FUEGO)
    {
        return true;
    }else
    {
        return false;
    }
}