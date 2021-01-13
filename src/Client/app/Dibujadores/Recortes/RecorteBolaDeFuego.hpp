#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP

#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteBolaDeFuego : public Recorte{
    static const int CANTIDAD_DE_RECORTES = 7;
    public:
        RecorteBolaDeFuego();
        SDL_Rect obtenerRecorte(int recorte) override;
        int obtenerAltura() override;
        int obtenerAnchura()override;
    private:
        SDL_Rect estadosPosibles[CANTIDAD_DE_RECORTES]{};

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
