#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP


#include "Recorte.hpp"

class RecorteFlor : public Recorte{
    public:
        RecorteFlor();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP
