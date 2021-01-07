#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_POZO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_POZO_HPP

#include <SDL2/SDL.h>
#include "Bloque.hpp"

class Pozo {

public:
    Pozo(int posicionX, int tipo);
    bool colisionaCon(Pozo* otroPozo);
    unsigned short obtenerPosicionX() const;

    SDL_Rect obtenerDimensiones();
    pozo_t serializar();

private:
    unsigned short posicionX;
    SDL_Rect dimensiones{};
    uint8_t tipo;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_POZO_HPP
