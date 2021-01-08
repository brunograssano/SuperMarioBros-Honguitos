#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORNIVEL_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORNIVEL_HPP

#include "../Cliente.hpp"
#include "src/Utils/Escuchador.hpp"

class EscuchadorNivel : public Escuchador{

    public:
        EscuchadorNivel(int socketCliente, Cliente* cliente);
        void casoError(int resultado)override;
        void casoSocketCerrado()override;
        void casoExitoso()override;
    private:
        bool recibioMensajeValido();
        string error;
        nivel_t info_nivel;
        Cliente* cliente;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESCUCHADORNIVEL_HPP
