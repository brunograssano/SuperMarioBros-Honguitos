#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP

#include "Sprite.hpp"

class SpriteBolaDeFuego : public Sprite{
    const int CICLOS_PARA_CAMBIO = 5;
    public:
        SpriteBolaDeFuego();
        ~SpriteBolaDeFuego() override = default;
        SDL_Rect obtenerRectanguloActual() override;
        void actualizarSprite() override;
        void explotar();
        bool terminoDeExplotar();

private:
        void cambiarSprite();
        SDL_Rect estadosPosibles[4]{};
        bool exploto;
        bool _terminoDeExplotar;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP