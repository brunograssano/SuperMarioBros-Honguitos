#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP

#include <queue>
#include "src/Utils/Enviador.hpp"

class EnviadorSonido : public Enviador{
    public:
        explicit EnviadorSonido(int socket);
        void enviar()override;
        void dejarInformacion(void* informacion)override;

    private:
        queue<sonido_t> colaSonidos;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP