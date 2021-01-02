#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP


#include <SDL2/SDL.h>
#include "Bloque.hpp"

class Tuberia {

    public:
        Tuberia(int posicionX, int tipo, int color);
        bool colisionaCon(Tuberia *otraTuberia);
        unsigned short obtenerPosicionX() const;

        SDL_Rect obtenerDimensiones();
        tuberia_t serializar();

private:
        unsigned short posicionX;
        SDL_Rect dimensiones{};
        uint8_t tipo;
        uint8_t color;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP
