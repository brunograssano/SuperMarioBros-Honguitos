#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP


#include "Recorte.hpp"

class RecorteFlor : public Recorte{
    public:
        RecorteFlor();
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP
