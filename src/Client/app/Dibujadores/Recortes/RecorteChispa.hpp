#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP

#include <SDL2/SDL.h>
#include "Recorte.hpp"
#include "src/Utils/Constantes.hpp"
class RecorteChispa : public Recorte{
    static const int CANTIDAD_DE_RECORTES = 4;
    public:
        RecorteChispa();
        SDL_Rect obtenerRecorte(int recorte) override;
        int direccion(int recorte) override;
        int obtenerAnchuraParaDibujarImagen()override;
        int obtenerAlturaParaDibujarImagen()override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP
