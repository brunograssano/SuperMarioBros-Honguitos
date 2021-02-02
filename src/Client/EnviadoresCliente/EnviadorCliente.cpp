#include "EnviadorCliente.hpp"

#include "EnviadorEntrada.hpp"
#include "EnviadorCredenciales.hpp"

EnviadorCliente::EnviadorCliente(Socket* socketCliente,Cliente* cliente) {
    enviadores[CREDENCIAL] = new EnviadorCredenciales(socketCliente);
    enviadores[ENTRADA] = new EnviadorEntrada(socketCliente);
    this->terminoEnviar = false;
    this->cliente = cliente;
}

void EnviadorCliente::ejecutar() {
    char tipoMensaje;
    bool hayError = false;
    while(!cliente->terminoElJuego() && !hayError){
        if(!identificadoresMensajeAEnviar.empty()){
            tipoMensaje = identificadoresMensajeAEnviar.front();
            identificadoresMensajeAEnviar.pop();
            try{
                enviadores[tipoMensaje]->enviar();
            }catch(const std::exception& e){
                hayError = true;
            }
        }
    }
    terminoEnviar = true;
    cliente->terminarProcesosDelCliente();
}

EnviadorCliente::~EnviadorCliente() {
    for(auto const& parClaveEnviador:enviadores){
        delete parClaveEnviador.second;
    }
    enviadores.clear();
}

void EnviadorCliente::agregarMensajeAEnviar(char tipoMensaje, void *mensaje) {
    enviadores[tipoMensaje]->dejarInformacion(mensaje);
    identificadoresMensajeAEnviar.push(tipoMensaje);
}

bool EnviadorCliente::terminoDeEnviar() {
    return terminoEnviar;
}