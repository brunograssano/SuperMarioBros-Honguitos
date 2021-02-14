#include "IntentadorIniciarModelo.hpp"

IntentadorIniciarModelo::IntentadorIniciarModelo(const unsigned int cantidadConexiones,AplicacionServidor *aplicacionServidor,
                                                 std::map<int, ConexionCliente*> *mapaClientesJugando,
                                                 std::map<int, std::string> *mapaIDNombre)
        : cantidadConexiones(cantidadConexiones) {
    this->aplicacionServidor = aplicacionServidor;
    this->mapaClientesJugando = mapaClientesJugando;
    this->mapaIDNombre = mapaIDNombre;
}

void IntentadorIniciarModelo::ejecutar() {
    info_partida_t info_partida[cantidadConexiones];
    while(mapaIDNombre->size() < cantidadConexiones){
        dormirHilo();
    }

    Log::getInstance()->mostrarMensajeDeInfo("Se va a iniciar el envio de informacion inicial a los jugadores.");

    for(auto parIDCliente:(*mapaClientesJugando)){
        int id = parIDCliente.first;
        info_partida[id] = aplicacionServidor->obtenerInfoPartida(*mapaIDNombre,id);
        parIDCliente.second->agregarMensajeAEnviar(PARTIDA,&info_partida[id]);
    }

    aplicacionServidor->iniciarJuego();
}
