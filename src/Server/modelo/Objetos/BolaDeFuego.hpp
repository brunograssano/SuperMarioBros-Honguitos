#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP

#include "src/Server/modelo/Objetos/Disparo.hpp"
#include "src/Server/modelo/PosicionMovil.hpp"
#include "src/Server/sprites/SpriteBolaDeFuego.hpp"

class BolaDeFuego : public Disparo{
    public:
        explicit BolaDeFuego(Posicion posicionInicial);
        void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        ~BolaDeFuego() override;

        bool debeDesaparecer() override;
    private:
        PosicionMovil* posicion;
        Sprite* sprite;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP
