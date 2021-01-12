#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ACEPTADORDECONEXIONES_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ACEPTADORDECONEXIONES_HPP

#include "src/Utils/Thread.hpp"
class Servidor;


class AceptadorDeConexiones : public Thread{

    public:
        explicit AceptadorDeConexiones(Servidor* servidor,int socketServer);
        void ejecutar()override;
        bool terminoAceptar() const;

    private:
        int socketServer;
        bool terminoHiloAceptar;
        Servidor* servidor;
        int crearCliente(int socketConexionEntrante, const struct sockaddr_in &addressCliente, int usuariosConectados);

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ACEPTADORDECONEXIONES_HPP
