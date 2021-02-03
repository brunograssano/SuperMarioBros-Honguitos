#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP
//rand() % (MAXIMO + 1 - MINIMO) + MINIMO
#include <queue>
#include "src/Utils/Enviador.hpp"

class EnviadorSonido : public Enviador{
    public:
        explicit EnviadorSonido(Socket* socket);
        void enviar()override;
        void dejarInformacion(void* informacion)override;

    private:
        std::queue<sonido_t> colaSonidos;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORSONIDO_HPP