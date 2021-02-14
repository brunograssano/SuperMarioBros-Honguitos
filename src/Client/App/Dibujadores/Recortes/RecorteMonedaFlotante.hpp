#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMONEDAFLOTANTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMONEDAFLOTANTE_HPP
#include "Recorte.hpp"

class RecorteMonedaFlotante : public Recorte{

    public:
        RecorteMonedaFlotante();
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMONEDAFLOTANTE_HPP
