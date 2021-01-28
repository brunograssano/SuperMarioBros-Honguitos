#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_POSICIONMOVIL_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_POSICIONMOVIL_HPP

#include "Posicion.hpp"
#include "PosicionFija.hpp"

class PosicionMovil : public Posicion{

    public:
        PosicionMovil(int coordenadaX,int coordenadaY, int minimoY, int minimoX, int maximoX);
        PosicionMovil(int coordenadaX, int coordenadaY);
        ~PosicionMovil() override = default;

        void moverHorizontal(float cantidadAMover);
        void moverVertical(float cantidadAMover);
        void actualizarLimiteTerrenoIzq(int limite);
        void actualizarLimiteTerrenoDer(int limite);

        void reiniciar(const Posicion& pos);

    private:
        int minimoX;
        int maximoX;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_POSICIONMOVIL_HPP
