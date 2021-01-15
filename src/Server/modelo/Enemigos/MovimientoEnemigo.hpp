#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOENEMIGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOENEMIGO_HPP

#include "src/Server/modelo/movimiento/MovimientoVertical.hpp"
#include "src/Server/modelo/movimiento/MovimientoHorizontalIdeal.hpp"

class MovimientoEnemigo {

    public:
        MovimientoEnemigo();
        ~MovimientoEnemigo() = default;
        void mover(PosicionMovil* posicionMovil);
        void setVelocidadY(float velocidadY);
        bool debeEspejarse();
        void morir();
        void cambiarOrientacion();

    private:
        static float obtenerVelocidad();
        MovimientoHorizontalIdeal movimientoHorizontal = MovimientoHorizontalIdeal(0.2);
        MovimientoVertical movimientoVertical = MovimientoVertical(0);

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOENEMIGO_HPP
