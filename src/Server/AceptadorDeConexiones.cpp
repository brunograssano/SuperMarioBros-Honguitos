#include "AceptadorDeConexiones.hpp"
#include "src/Utils/Utils.hpp"
#include "ConexionCliente.hpp"
#include "Servidor.hpp"

AceptadorDeConexiones::AceptadorDeConexiones(Servidor *servidor,int socketServer) {
    this->servidor = servidor;
    this->socketServer = socketServer;
    terminoHiloAceptar = false;
}

int AceptadorDeConexiones::crearCliente(int socketConexionEntrante,const struct sockaddr_in &addressCliente, int usuariosConectados) {
    if (socketConexionEntrante < 0) {
        Log::getInstance()->huboUnError("No se pudo aceptar una conexion proveniente de "+ (string) (inet_ntoa(addressCliente.sin_addr))+ " del puerto "+ to_string(ntohs(addressCliente.sin_port)) + ".");
    } else {
        Log::getInstance()->mostrarMensajeDeInfo("Se obtuvo una conexion de "+ (string) (inet_ntoa(addressCliente.sin_addr))+ " del puerto "+ to_string(ntohs(addressCliente.sin_port)) + ".");
        actualizacion_cantidad_jugadores_t actualizacion = servidor->crearActualizacionJugadores();

        auto *conexion = new ConexionCliente(servidor,socketConexionEntrante,servidor->cantidadUsuariosLogueados(), (string) (inet_ntoa(addressCliente.sin_addr)), actualizacion);

        try{
            conexion->empezarHilo("ConexionCliente("+to_string(usuariosConectados) +" - "+ (string) inet_ntoa(addressCliente.sin_addr)+")");
            usuariosConectados++;
            servidor->guardarConexion(conexion);
        }catch (const std::exception& e) {
            delete conexion;
        }
    }

    return usuariosConectados;
}


void AceptadorDeConexiones::ejecutar() {
    int usuariosConectados = 0;
    int socketConexionEntrante = 0;
    socklen_t addressStructure = 0;
    struct sockaddr_in addressCliente{};
    memset(&addressCliente,0,sizeof(sockaddr_in));

    while(!servidor->terminoElJuego()){
        socketConexionEntrante = accept(socketServer, (struct sockaddr *) &addressCliente, &addressStructure);
        if(!servidor->terminoElJuego()){
            usuariosConectados = crearCliente(socketConexionEntrante,addressCliente, usuariosConectados);
        }
    }
    terminoHiloAceptar = true;
}

bool AceptadorDeConexiones::terminoAceptar() const{
    return terminoHiloAceptar;
}