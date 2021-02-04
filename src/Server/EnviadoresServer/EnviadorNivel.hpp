#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORNIVEL_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORNIVEL_HPP

#include "../../Utils/Enviador.hpp"

class EnviadorNivel : public Enviador{

    public:
        explicit EnviadorNivel(Socket* socket);
        void enviar()override;
        void dejarInformacion(void* informacionNivel)override;
    private:
        nivel_t info_nivel{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ENVIADORNIVEL_HPP