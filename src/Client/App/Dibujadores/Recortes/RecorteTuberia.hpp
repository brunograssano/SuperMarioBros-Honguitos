#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTETUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTETUBERIA_HPP

#include <SDL.h>
#include "Recorte.hpp"

class RecorteTuberia: public Recorte {
    public:
        RecorteTuberia();
        int obtenerAlturaParaDibujarImagen(int tipo) override;
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTETUBERIA_HPP
