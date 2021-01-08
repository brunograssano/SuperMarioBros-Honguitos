#include "EscuchadorCliente.hpp"

#include "EscuchadorVerificacionCredenciales.hpp"
#include "EscuchadorActualizacionJugadores.hpp"
#include "EscuchadorInfoPartidaInicial.hpp"
#include "EscuchadorRonda.hpp"
#include "EscuchadorSonido.hpp"
#include "EscuchadorLog.hpp"
#include "EscuchadorNivel.hpp"

EscuchadorCliente::EscuchadorCliente(int socketCliente,Cliente* cliente,bool* terminoJuego,bool* terminoEscuchar) {
    escuchadores[VERIFICACION] = new EscuchadorVerificacionCredenciales(socketCliente, cliente);
    escuchadores[ACTUALIZACION_JUGADORES] = new EscuchadorActualizacionJugadores(socketCliente, cliente);
    escuchadores[MENSAJE_LOG] = new EscuchadorLog(socketCliente);
    escuchadores[PARTIDA] = new EscuchadorInfoPartidaInicial(socketCliente,cliente);
    escuchadores[RONDA] = new EscuchadorRonda(socketCliente, cliente);
    escuchadores[SONIDO] = new EscuchadorSonido(socketCliente);
    escuchadores[NIVEL] = new EscuchadorNivel(socketCliente,cliente);
    this->socketCliente = socketCliente;
    this->terminoJuego = terminoJuego;
    this->terminoEscuchar = terminoEscuchar;
    this->cliente = cliente;
}

EscuchadorCliente::~EscuchadorCliente() {
    for(auto const& parClaveEscuchador:escuchadores){
        delete parClaveEscuchador.second;
    }
    escuchadores.clear();
}

void EscuchadorCliente::escuchar() {
    char tipoMensaje;
    int resultado;
    bool hayError = false;

    while(!hayError && !(*terminoJuego)){
        resultado = recv(socketCliente, &tipoMensaje, sizeof(char), MSG_WAITALL);

        if(resultado<0){
            Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje",to_string(errno));
            hayError = true;
        }else if(resultado == 0){
            Log::getInstance()->mostrarMensajeDeInfo("Se desconecto el socket que escucha al server. ----- " +to_string(errno));
            hayError = true;
        }
        else{
            try{
                escuchadores[tipoMensaje]->escuchar();
            }catch(const std::exception& e){
                hayError = true;
            }
        }
    }
    (*terminoEscuchar) = true;
    cliente->terminarProcesosDelCliente();
}
