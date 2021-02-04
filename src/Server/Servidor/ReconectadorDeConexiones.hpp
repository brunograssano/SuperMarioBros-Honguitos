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
        void agregarUsuarioDesconectado(const std::string &nombre, const std::string &contrasenia, int idJugador);
        bool estaDesconectado(const std::string &nombre);

private:
        bool terminoHilo;
        bool terminarReconectar;
        void reconectadorFaseJuego(usuario_t usuario, int idJugador);
        Servidor* servidor;
        std::map<int,usuario_t> usuariosQuePerdieronConexion;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECONECTADORDECONEXIONES_HPP
