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
    private:
        void cambiarSprite();
        SDL_Rect estadosPosibles[4]{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP