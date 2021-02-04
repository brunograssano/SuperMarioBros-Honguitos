#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ACEPTADORDECONEXIONES_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ACEPTADORDECONEXIONES_HPP

#include "src/Utils/Socket.hpp"
#include "src/Utils/Thread.hpp"
class Servidor;


class AceptadorDeConexiones : public Thread{

    public:
        explicit AceptadorDeConexiones(Servidor* servidor,Socket* socketServer);
        void ejecutar()override;
        bool terminoAceptar() const;

    private:
        Socket* socketServer;
        bool terminoHiloAceptar;
        Servidor* servidor;
        int crearCliente(Socket socketConexionEntrante, int usuariosConectados);

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ACEPTADORDECONEXIONES_HPP
