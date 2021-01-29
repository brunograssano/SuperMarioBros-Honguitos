#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP

#include "Recorte.hpp"
class RecorteChispa : public Recorte{
    static const int CANTIDAD_DE_RECORTES = 4;
    public:
        RecorteChispa();
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP
