#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECONECTADORDECONEXIONES_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECONECTADORDECONEXIONES_HPP

#include <map>
#include "src/Utils/Utils.hpp"
#include "src/Utils/Thread.hpp"
class Servidor;

class ReconectadorDeConexiones : public Thread{

    public:
        explicit ReconectadorDeConexiones(Servidor* servidor);
        void ejecutar()override;
        void terminarReconectarConexiones();
        bool coincideAlgunaCredencial(const usuario_t &usuario, int *credencialNuevoJugador);
        bool terminoHiloReconectar() const;
        void agregarUsuarioDesconectado(const string &nombre, const string &contrasenia, const int idJugador);
        bool estaDesconectado(const string &nombre);

private:
        bool terminoHilo;
        bool terminarReconectar;
        void reconectadorFaseJuego(usuario_t usuario, int idJugador);
        Servidor* servidor;
        map<int,usuario_t> usuariosQuePerdieronConexion;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECONECTADORDECONEXIONES_HPP
