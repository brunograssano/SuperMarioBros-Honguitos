#include "EscuchadorPodio.hpp"
#include "src/Utils/log/Log.hpp"

EscuchadorPodio::EscuchadorPodio(Socket* socketCliente, Cliente *cliente) {
    this->socket = socketCliente;
    this->cliente = cliente;
    structPointer = &this->ultimos_podios;
    bytes = sizeof(ultimos_podios_t);
    error = std::string("");
}

void EscuchadorPodio::casoError(int resultado) {
    Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion del podio, se cierra el socket", std::to_string(errno));
    throw std::runtime_error("ErrorAlEscucharInformacionDelPodio");
}

void EscuchadorPodio::casoSocketCerrado() {
    Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion del podio, se cierra el socket");
    throw std::runtime_error("ErrorAlEscucharInformacionDelPodio");
}

void EscuchadorPodio::casoExitoso() {
    cliente->recibirInformacionPodios(ultimos_podios);
}