#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORSONIDO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORSONIDO_HPP

#include "src/Utils/Escuchador.hpp"

class EscuchadorSonido : public Escuchador{
    public:
        explicit EscuchadorSonido(int socketCliente);
        ~EscuchadorSonido() override;
        void casoError(int resultado)override;
        void casoSocketCerrado()override;
        void casoExitoso()override;

    private:
        sonido_t sonido;
        string error;

    bool recibioMensajeValido();
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORSONIDO_HPP