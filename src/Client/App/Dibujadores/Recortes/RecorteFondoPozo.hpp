#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFONDOPOZO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFONDOPOZO_HPP

#include "Recorte.hpp"

class RecorteFondoPozo : public Recorte{
    public:
        RecorteFondoPozo();
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFONDOPOZO_HPP
