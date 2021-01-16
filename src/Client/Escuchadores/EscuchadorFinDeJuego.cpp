
#include "EscuchadorFinDeJuego.hpp"

EscuchadorFinDeJuego::EscuchadorFinDeJuego(int socketCliente, Cliente* cliente) {
    this->socket = socketCliente;
    this->cliente = cliente;
    this->structPointer = &this->infoFinJuego; /*QUE HACE ESTO*/
    this->bytes = sizeof(info_fin_juego_t);
}

void EscuchadorFinDeJuego::casoSocketCerrado() {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion final del juego, se cierra el socket");
    throw runtime_error("ErrorAlEscucharInformacionFinalJuego");
}

void EscuchadorFinDeJuego::casoError(int resultado) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de informacion final del juego, se cierra el socket", to_string(errno));
    throw runtime_error("ErrorAlEscucharInformacionDeInformacionFinalJuego");
}

void EscuchadorFinDeJuego::casoExitoso() {
    this->cliente->recibirInformacionFinJuego(this->infoFinJuego);
}