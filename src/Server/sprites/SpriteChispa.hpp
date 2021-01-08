#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP

#include "Sprite.hpp"

class SpriteChispa : public Sprite{
    public:
        SpriteChispa();
        ~SpriteChispa() override = default;
        SDL_Rect obtenerRectanguloActual() override;
        void actualizarSprite() override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
