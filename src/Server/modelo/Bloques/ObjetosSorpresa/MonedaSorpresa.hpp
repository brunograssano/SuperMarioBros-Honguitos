#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP


#include "ObjetoSorpresa.hpp"
#include "src/Server/modelo/PosicionMovil.hpp"
#include "src/Server/modelo/movimiento/MovimientoVertical.hpp"
#include <src/Server/sprites/SpriteMonedaFlotante.hpp>

class MonedaSorpresa : public ObjetoSorpresa{
    public:
        explicit MonedaSorpresa(Posicion* posicionInicial);
        void usarse(Mario* mario)override;
        efecto_t serializar() override;
        void actualizar() override;
        int obtenerPosicionX() override;
        string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;

    private:
        void inicializarMapasDeColision() override;
        PosicionMovil posicion = PosicionMovil(0, 0, 0, 0, 0);
        MovimientoVertical movimiento = MovimientoVertical(0);
        SpriteMonedaFlotante sprite;
        int posYInicial;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP
