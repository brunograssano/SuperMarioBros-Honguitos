#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP

#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteBolaDeFuego : public Recorte{

    public:
        RecorteBolaDeFuego();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEBOLADEFUEGO_HPP
