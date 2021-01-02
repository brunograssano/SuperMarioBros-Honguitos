#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTETUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTETUBERIA_HPP

#include <SDL.h>

const unsigned short MAX_TIPOS = 2;

class RecorteTuberia {

    public:
        RecorteTuberia();
        SDL_Rect obtenerRecorte(uint8_t tipo, uint8_t color);

    private:
        SDL_Rect recortesTuberias[MAX_TIPOS]{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTETUBERIA_HPP
