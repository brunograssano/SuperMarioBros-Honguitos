#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBLOQUE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBLOQUE_HPP

#include "Sprite.hpp"

class SpriteBloque : public Sprite{

    public:
        ~SpriteBloque() override = default;
        virtual void usarse() = 0;
        virtual bool cambioElSprite() = 0;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBLOQUE_HPP
