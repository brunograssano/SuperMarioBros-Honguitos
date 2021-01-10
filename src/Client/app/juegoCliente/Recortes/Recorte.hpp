#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP

#include <SDL2/SDL.h>

class Recorte {
    public:
        virtual SDL_Rect obtenerRecorte(int recorte) = 0;
        virtual int obtenerAltura() = 0;
        virtual int obtenerAnchura() = 0;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP
