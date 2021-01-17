#include "EnviadorConexionCliente.hpp"

#include "EnviadorEstadoCredencial.hpp"
#include "EnviadorRonda.hpp"
#include "EnviadorMensajeLog.hpp"
#include "EnviadorInfoPartida.hpp"
#include "EnviadorCantidadConexion.hpp"
#include "EnviadorSonido.hpp"
#include "EnviadorNivel.hpp"

EnviadorConexionCliente::EnviadorConexionCliente(int socket,ConexionCliente* cliente) {
    this->cliente = cliente;
    enviadores[VERIFICACION] = new EnviadorEstadoCredencial(socket);
    enviadores[RONDA] = new EnviadorRonda(socket);
    enviadores[MENSAJE_LOG] = new EnviadorMensajeLog(socket);
    enviadores[PARTIDA] = new EnviadorInfoPartida(socket);
    enviadores[ACTUALIZACION_JUGADORES] = new EnviadorCantidadConexion(socket);
    enviadores[SONIDO] = new EnviadorSonido(socket);
    enviadores[NIVEL] = new EnviadorNivel(socket);
}

void EnviadorConexionCliente::ejecutar() {
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
    cliente->terminarElJuego();
}


void EnviadorConexionCliente::agregarMensajeAEnviar(char caracter,void* mensaje) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    enviadores[caracter]->dejarInformacion(mensaje);
    pthread_mutex_lock(&mutex);
    identificadoresMensajeAEnviar.push(caracter);
    pthread_mutex_unlock(&mutex);
}

EnviadorConexionCliente::~EnviadorConexionCliente() {
    for(auto const& parClaveEnviador:enviadores){
        delete parClaveEnviador.second;
    }
}
