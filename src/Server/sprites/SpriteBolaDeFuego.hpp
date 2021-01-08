#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP

#include "Sprite.hpp"

class SpriteBolaDeFuego : public Sprite{
    public:
        SpriteBolaDeFuego();
        ~SpriteBolaDeFuego() override = default;
        SDL_Rect obtenerRectanguloActual() override;
        void actualizarSprite() override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP