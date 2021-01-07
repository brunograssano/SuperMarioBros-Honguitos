#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CAMARA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CAMARA_HPP

#include <SDL2/SDL.h>
#include <map>
#include "../Mario/Mario.hpp"
#include "src/Utils/Constantes.hpp"
/*
 * Es el ancho que se permite hacia adelante y hacia atrás de la pantalla
 * para considerar a una entidad que está en el rango de visión
 */
const int ANCHO_RANGO = 100;


class Camara {

    public:
        Camara(int alto_pantalla, int ancho_pantalla);
        ~Camara();
        void reiniciar();
        void moverCamara(const map<int,Mario*>& jugadores);
        static bool estaEnRangoHelper(void* ptr, int x){
            return (((Camara*) ptr)->estaEnRangoVisible(x));
        }
        bool estaEnRangoVisible(int posicionX);
        SDL_Rect obtenerRectanguloCamara();
    private:
        SDL_Rect rectanguloCamara;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CAMARA_HPP
