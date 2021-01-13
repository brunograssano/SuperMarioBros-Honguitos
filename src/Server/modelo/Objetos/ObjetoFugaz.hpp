#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOFUGAZ_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOFUGAZ_HPP

#include "src/Utils/Utils.hpp"

class ObjetoFugaz {
    public:
        virtual bool debeDesaparecer() = 0;

        virtual efecto_t serializar() = 0;

        virtual void actualizar() = 0;

        virtual int obtenerPosicionX() = 0;

        virtual ~ObjetoFugaz() = default;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOFUGAZ_HPP