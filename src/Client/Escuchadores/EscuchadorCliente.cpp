#include "EscuchadorCliente.hpp"

#include "EscuchadorVerificacionCredenciales.hpp"
#include "EscuchadorActualizacionJugadores.hpp"
#include "EscuchadorInfoPartidaInicial.hpp"
#include "EscuchadorRonda.hpp"
#include "EscuchadorSonido.hpp"
#include "EscuchadorLog.hpp"
#include "EscuchadorNivel.hpp"
#include "EscuchadorPodio.hpp"

EscuchadorCliente::EscuchadorCliente(Socket* socket, Cliente* cliente) {
    escuchadores[VERIFICACION] = new EscuchadorVerificacionCredenciales(socket, cliente);
    escuchadores[ACTUALIZACION_JUGADORES] = new EscuchadorActualizacionJugadores(socket, cliente);
    escuchadores[MENSAJE_LOG] = new EscuchadorLog(socket);
    escuchadores[PARTIDA] = new EscuchadorInfoPartidaInicial(socket, cliente);
    escuchadores[RONDA] = new EscuchadorRonda(socket, cliente);
    escuchadores[SONIDO] = new EscuchadorSonido(socket);
    escuchadores[NIVEL] = new EscuchadorNivel(socket, cliente);
    escuchadores[PODIO] = new EscuchadorPodio(socket, cliente);
    this->socketCliente = socket;
    this->terminoEscuchar = false;
    this->cliente = cliente;
}

EscuchadorCliente::~EscuchadorCliente() {
    for(auto const& parClaveEscuchador:escuchadores){
        delete parClaveEscuchador.second;
    }
    escuchadores.clear();
}

void EscuchadorCliente::ejecutar() {
    char tipoMensaje;
    int resultado;
    bool hayError = false;

    while(!hayError && !cliente->terminoElJuego()){
        resultado = socketCliente->escuchar(&tipoMensaje, sizeof(char));

        if(resultado<0){
            Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje",std::to_string(errno));
            hayError = true;
        }else if(resultado == 0){
            Log::getInstance()->mostrarMensajeDeInfo("Se desconecto el socket que escucha al server. ----- " +std::to_string(errno));
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
    terminoEscuchar = true;
    cliente->terminarProcesosDelCliente();
}

bool EscuchadorCliente::terminoDeEscuchar() const {
    return terminoEscuchar;
}