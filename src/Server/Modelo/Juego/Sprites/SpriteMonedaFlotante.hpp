#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEMONEDAFLOTANTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEMONEDAFLOTANTE_HPP

#include "Sprite.hpp"

class SpriteMonedaFlotante : public Sprite{
    public:
        SpriteMonedaFlotante();
        int obtenerEstadoActual() override;
        void actualizarSprite() override;
    private:
        void cambiarSprite();

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEMONEDAFLOTANTE_HPP
