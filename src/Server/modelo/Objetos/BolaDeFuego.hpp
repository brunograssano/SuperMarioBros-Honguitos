#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP

#include <src/Server/modelo/PosicionFija.hpp>
#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/PosicionMovil.hpp"
#include "src/Server/sprites/SpriteBolaDeFuego.hpp"
#include "src/Utils/Constantes.hpp"

class BolaDeFuego : public ObjetoFugaz{
    const float VELOCIDAD_X_INICIAL = 3.5;
    const float VELOCIDAD_Y_INICIAL = 0;
    const float EFECTO_GRAVITACIONAL = -0.1;
    public:
        explicit BolaDeFuego(PosicionFija posicionInicial, int direccion, float velocidadDeInercia);

    void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        ~BolaDeFuego() override;

        bool debeDesaparecer() override;
    private:
        PosicionMovil* posicion;
        Sprite* sprite;
        float velocidadX;
        float velocidadY;
        int rebotes = 0;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP
