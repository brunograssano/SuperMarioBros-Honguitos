#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP

#include <SDL2/SDL.h>

class RecorteBolaDeFuego {
    static const int CANTIDAD_DE_RECORTES = 4;
    public:
        RecorteBolaDeFuego();
        SDL_Rect obtenerRecorte(int recorte);
    private:
        SDL_Rect estadosPosibles[CANTIDAD_DE_RECORTES];

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
