#include "AceptadorDeConexiones.hpp"
#include "Servidor.hpp"

AceptadorDeConexiones::AceptadorDeConexiones(Servidor *servidor,Socket* socketServer) {
    this->servidor = servidor;
    this->socketServer = socketServer;
    terminoHiloAceptar = false;
}

int AceptadorDeConexiones::crearCliente(Socket socketConexionEntrante, int usuariosConectados) {
    Log::getInstance()->mostrarMensajeDeInfo("Se obtuvo una conexion de "+socketConexionEntrante.obtenerIP()+".");
    actualizacion_cantidad_jugadores_t actualizacion = servidor->crearActualizacionJugadores();

    auto *conexion = new ConexionCliente(servidor, std::move(socketConexionEntrante), actualizacion);

    try{
        conexion->empezarHilo("ConexionCliente("+conexion->obtenerIP()+")");
        usuariosConectados++;
        servidor->guardarConexion(conexion);
    }catch (const std::exception& e) {
        delete conexion;
    }
    return usuariosConectados;
}


void AceptadorDeConexiones::ejecutar() {
    int usuariosConectados = 0;

    while(!servidor->terminoElJuego()){
        try{
            Socket socketConexionEntrante = socketServer->accept();
            if(!servidor->terminoElJuego()){
                usuariosConectados = crearCliente(std::move(socketConexionEntrante), usuariosConectados);
            }
        }catch(std::exception& e){
            if(!servidor->terminoElJuego()){
                Log::getInstance()->huboUnError(e.what());
            }
        }

    }
    terminoHiloAceptar = true;
}

bool AceptadorDeConexiones::terminoAceptar() const{
    return terminoHiloAceptar;
}