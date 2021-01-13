#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP

#include <SDL2/SDL.h>
#include "src/Utils/Constantes.hpp"
class Recorte {
    public:
        virtual ~Recorte() = default;
        virtual SDL_Rect obtenerRecorte(int recorte) = 0;
        virtual int obtenerAltura() = 0;
        virtual int obtenerAnchura() = 0;
        virtual int direccion(int recorte) {
                return DERECHA;
        }

    virtual void actualizarSprite(){};
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP
