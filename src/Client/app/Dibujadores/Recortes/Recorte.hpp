#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP

#include <SDL2/SDL.h>
#include "src/Utils/Constantes.hpp"
#include <list>

class Recorte {
    public:
        virtual ~Recorte() = default;
        virtual SDL_Rect obtenerRecorte(int recorte);
        virtual SDL_Rect obtenerRecorte(int recorte, int tipoBloque);
        virtual int obtenerAlturaParaDibujarImagen();
        virtual int obtenerAnchuraParaDibujarImagen();
        virtual int direccion(int recorte);
        virtual void actualizarSprite(){};

    protected:
        void inicializarEstados(int cantidadEstados,int desplazamientoEnX,int alto, int ancho);
        std::list<SDL_Rect> estadosPosibles;

};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTE_HPP
