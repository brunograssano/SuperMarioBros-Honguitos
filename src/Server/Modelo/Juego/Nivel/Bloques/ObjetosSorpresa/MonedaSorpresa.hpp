#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP


#include "ObjetoSorpresa.hpp"
#include "src/Server/Modelo/Juego/Colisionable.hpp"
#include "src/Server/Modelo/Juego/Posiciones/Posicion.hpp"
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Utils/Utils.hpp"
#include "src/Server/Modelo/Juego/Sprites/SpriteMonedaFlotante.hpp"

class MonedaSorpresa : public ObjetoSorpresa{
    public:
        explicit MonedaSorpresa(Posicion* posicionInicial);
        void usarse(Mario* mario)override;
        entidad_t serializar() override;
        void actualizar() override;
        int obtenerPosicionX() override;
        int tipoDeEfecto() override;
        std::string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;

    private:
        void inicializarMapasDeColision() override;
        PosicionMovil posicion;
        MovimientoVertical movimiento;
        SpriteMonedaFlotante sprite;
        int posYInicial;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP
