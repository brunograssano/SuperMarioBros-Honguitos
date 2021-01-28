#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP


#include <SDL2/SDL.h>
#include "Bloque.hpp"
#include "PiezaDeTuberia.hpp"

class Tuberia{

    public:
        Tuberia(int posicionX, int tipo, int color);
        bool colisionaCon(Tuberia *otraTuberia);
        unsigned short obtenerPosicionX() const;
        void elevar(int y);
        SDL_Rect obtenerDimensiones();
        entidad_t serializar();
        list<PiezaDeTuberia*> obtenerPiezas();
    private:
        void crearColisionables(int x, int tipo);
        list<PiezaDeTuberia*> piezas;
        Posicion posicion;
        SDL_Rect dimensiones{};
        uint8_t tipo;
        uint8_t color;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP
