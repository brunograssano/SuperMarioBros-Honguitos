
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CABEZAENEMIGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CABEZAENEMIGO_HPP


#include "Terreno.hpp"

class CabezaEnemigo : public Terreno{
    public:
        CabezaEnemigo();
        float aplicarCoeficienteDeRozamiento(float velocidadX) override;
        float obtenerImpulsoHorizontal(float aceleracion) override;
        float obtenerImpulsoVertical(float fuerza) override;
        float amortiguarVelocidad(float velocidadY) override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CABEZAENEMIGO_HPP
