#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOHORIZONTALIDEAL_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOHORIZONTALIDEAL_HPP


#include "src/Server/modelo/PosicionMovil.hpp"

class MovimientoHorizontalIdeal {
    public:
        explicit MovimientoHorizontalIdeal(float velocidad);
        void mover(PosicionMovil* posicion);
        void setVelocidad(float velocidad);
        void cambiarDireccion();
        bool debeEspejarse() const;

    private:
        float velocidadX;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MOVIMIENTOHORIZONTALIDEAL_HPP
