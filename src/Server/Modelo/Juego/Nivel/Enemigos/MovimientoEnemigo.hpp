#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOENEMIGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOENEMIGO_HPP

#include "src/Server/Modelo/Juego/Movimientos/MovimientoVertical.hpp"
#include "src/Server/Modelo/Juego/Movimientos/MovimientoHorizontalIdeal.hpp"

class MovimientoEnemigo {

    public:
        explicit MovimientoEnemigo(float velocidadExtra);
        ~MovimientoEnemigo() = default;
        void mover(PosicionMovil* posicionMovil);
        void setVelocidadY(float velocidadY);
        bool debeEspejarse();
        void morir();
        void cambiarOrientacion();

    private:
        static float obtenerVelocidad(float velocidadExtra);
        MovimientoHorizontalIdeal movimientoHorizontal = MovimientoHorizontalIdeal(0.2);
        MovimientoVertical movimientoVertical = MovimientoVertical(0);

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOENEMIGO_HPP
