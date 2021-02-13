#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP

#include "src/Utils/ColaBloqueante.hpp"
#include "src/Utils/Enviador.hpp"
#include "src/Utils/Utils.hpp"

class EnviadorSonido : public Enviador{
    public:
        explicit EnviadorSonido(Socket* socket);
        void enviar()override;
        void dejarInformacion(void* informacion)override;

    private:
        BlockingQueue<sonido_t> colaSonidos;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP