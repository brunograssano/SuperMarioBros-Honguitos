#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_VACIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_VACIO_HPP

#include "Terreno.hpp"

class Vacio : public Terreno{

    public:
        float aplicarCoeficienteDeRozamiento(float velocidadX) override;
        float obtenerImpulsoHorizontal(float aceleracion) override;
        float obtenerImpulsoVertical(float fuerza) override;
        float amortiguarVelocidad(float velocidadY) override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_VACIO_HPP
