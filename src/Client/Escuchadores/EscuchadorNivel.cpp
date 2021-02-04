#include "EscuchadorNivel.hpp"
#include "src/Utils/log/Log.hpp"

EscuchadorNivel::EscuchadorNivel(int socketCliente, Cliente *cliente) {
    this->socket = socketCliente;
    this->cliente = cliente;
    structPointer = &this->info_nivel;
    bytes = sizeof(nivel_t);
    error = std::string("");
}

void EscuchadorNivel::casoError(int resultado) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion del nivel, se cierra el socket", std::to_string(errno));
    throw std::runtime_error("ErrorAlEscucharInformacionDelNivel");
}

void EscuchadorNivel::casoSocketCerrado() {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion del nivel, se cierra el socket");
    throw std::runtime_error("ErrorAlEscucharInformacionDelNivel");
}

void EscuchadorNivel::casoExitoso() {
    cliente->recibirInformacionNivel(info_nivel);
}
