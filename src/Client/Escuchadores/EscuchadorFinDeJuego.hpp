
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORFINDEJUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORFINDEJUEGO_HPP


#include <src/Utils/Escuchador.hpp>
#include "../Cliente.hpp"

class EscuchadorFinDeJuego : public Escuchador{
    public:
        EscuchadorFinDeJuego(int socketCliente, Cliente* cliente);
        void casoError(int resultado)override;
        void casoSocketCerrado()override;
        void casoExitoso()override;

    private:
        info_fin_juego_t infoFinJuego;
        Cliente* cliente;
        string error;
};



#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORFINDEJUEGO_HPP
