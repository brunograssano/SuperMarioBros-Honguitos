#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP

#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteBolaDeFuego : public Recorte{

    public:
        RecorteBolaDeFuego();
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
