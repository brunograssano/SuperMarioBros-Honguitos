#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEPOZO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEPOZO_HPP


#include "Recorte.hpp"

class RecortePozo : public Recorte{
    public:
        RecortePozo();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEPOZO_HPP
