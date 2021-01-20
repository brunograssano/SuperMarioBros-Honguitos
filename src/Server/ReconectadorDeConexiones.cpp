#include "ReconectadorDeConexiones.hpp"
#include "UtilidadesServer.hpp"
#include "Servidor.hpp"

ReconectadorDeConexiones::ReconectadorDeConexiones(Servidor *servidor) {
    this->servidor = servidor;
    terminoHilo = false;
    terminarReconectar = false;
}

void ReconectadorDeConexiones::ejecutar() {
    list<int> idsUsuariosReconectados;
    while(!terminarReconectar){
        while(usuariosQuePerdieronConexion.empty()){
            dormirHilo();
        }
        for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
            usuario_t usuario = parClaveUsuario.second;
            if(usuario.usado){
                int idJugador = parClaveUsuario.first;
                if(!servidor->empezoElJuego()){
                    servidor->mandarActualizacionAClientes();
                }else{
                    reconectadorFaseJuego(usuario,idJugador);
                }
                pthread_mutex_lock(&mutex);
                idsUsuariosReconectados.push_front(idJugador);
                pthread_mutex_unlock(&mutex);
            }
        }
        for(auto const id:idsUsuariosReconectados){
            usuariosQuePerdieronConexion.erase(id);
        }
        if(!idsUsuariosReconectados.empty()){
            idsUsuariosReconectados.clear();
        }
    }
    terminoHilo = true;
}

void ReconectadorDeConexiones::reconectadorFaseJuego(usuario_t usuario, const int idJugador) {
    mensaje_log_t mensajeLog;
    memset(&mensajeLog, 0, sizeof(mensaje_log_t));
    usuario.nombre.insert(0, "Se reconecto el usuario: ");
    strcpy(mensajeLog.mensajeParaElLog,usuario.nombre.c_str());
    mensajeLog.tipo = INFO;
    servidor->reconectarJugador(mensajeLog,idJugador);
}

void ReconectadorDeConexiones::terminarReconectarConexiones() {
    terminarReconectar = true;
}

bool ReconectadorDeConexiones::coincideAlgunaCredencial(const usuario_t &usuario, int *credencialNuevoJugador) {
    for(auto& parClaveUsuario:usuariosQuePerdieronConexion){
        if(coincidenCredenciales(usuario, parClaveUsuario.second)){
            (*credencialNuevoJugador) = parClaveUsuario.first;
            parClaveUsuario.second.usado = true;
            return true;
        }
    }
    return false;
}

void ReconectadorDeConexiones::agregarUsuarioDesconectado(const string &nombre, const string &contrasenia, const int idJugador) {
    usuario_t usuarioDesconectado = {nombre,contrasenia,false};
    usuariosQuePerdieronConexion[idJugador] = usuarioDesconectado;
}

bool ReconectadorDeConexiones::terminoHiloReconectar() const {
    return terminoHilo;
}

bool ReconectadorDeConexiones::estaDesconectado(const string& nombre){
    bool estaDesconectado = false;
    for(auto const& parClaveUsuario:usuariosQuePerdieronConexion){
        if(nombre == parClaveUsuario.second.nombre && !parClaveUsuario.second.usado){
            estaDesconectado = true;
        }
    }
    return estaDesconectado;
}