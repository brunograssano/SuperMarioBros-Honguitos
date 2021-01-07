#include "EscuchadorConexionCliente.hpp"

class EscuchadorEntradaTeclado;
#include "EscuchadorEntradaTeclado.hpp"
#include "EscuchadorCredenciales.hpp"

#define SIN_JUGAR -1

EscuchadorConexionCliente::EscuchadorConexionCliente(int socket,bool* terminoJuego,ConexionCliente* cliente,Servidor* servidor) {
    escuchadores[CREDENCIAL] = new EscuchadorCredenciales(socket,cliente);
    this->socket = socket;
    this->cliente = cliente;
    this->servidor = servidor;
    this->terminoJuego = terminoJuego;
    idJugador = SIN_JUGAR;
}

EscuchadorConexionCliente::~EscuchadorConexionCliente() {
    for(auto const& parClaveEscuchador:escuchadores){
        delete parClaveEscuchador.second;
    }
    escuchadores.clear();
}

void EscuchadorConexionCliente::escuchar() {
    char tipoMensaje;
    int resultado;
    bool hayError = false;
    while(!(*terminoJuego) && !hayError){

        resultado = recv(socket, &tipoMensaje, sizeof(char), MSG_WAITALL);

        if(resultado<0){
            Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje en el cliente: " + cliente->obtenerIP(), to_string(errno));
            hayError = true;
        }else if(resultado == 0){
            Log::getInstance()->mostrarMensajeDeInfo("Se desconecto el socket que escucha al cliente: " + cliente->obtenerIP() + " ---- "+ to_string(errno));
            hayError = true;
        }else{
            try{
                escuchadores[tipoMensaje]->escuchar();
            }catch(const std::exception& e){
                hayError = true;
            }
        }
    }
    servidor->agregarUsuarioDesconectado(cliente,idJugador);
    (*terminoJuego) = true;
}

void EscuchadorConexionCliente::agregarEscuchadorEntrada(int IDjugador) {
    escuchadores[ENTRADA] = new EscuchadorEntradaTeclado(socket,IDjugador,servidor);
    idJugador = IDjugador;
}
