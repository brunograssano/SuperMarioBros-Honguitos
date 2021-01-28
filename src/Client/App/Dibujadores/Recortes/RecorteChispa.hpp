#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP

#include "Recorte.hpp"
class RecorteChispa : public Recorte{
    static const int CANTIDAD_DE_RECORTES = 4;
    public:
        RecorteChispa();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTECHISPA_HPP
