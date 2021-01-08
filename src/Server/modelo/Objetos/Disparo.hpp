#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_DISPARO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_DISPARO_HPP

#include "src/Utils/Utils.hpp"

class Disparo {
    public:
        virtual bool debeDesaparecer() = 0;

        virtual efecto_t serializar() = 0;

        virtual void actualizar() = 0;

        virtual int obtenerPosicionX() = 0;

        virtual ~Disparo() = default;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_DISPARO_HPP