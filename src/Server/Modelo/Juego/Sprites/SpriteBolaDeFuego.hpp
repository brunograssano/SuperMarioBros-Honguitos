#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP

#include "Sprite.hpp"

class SpriteBolaDeFuego : public Sprite{

    public:
        SpriteBolaDeFuego();
        ~SpriteBolaDeFuego() override = default;
        void actualizarSprite() override;
        void explotar();
        bool terminoDeExplotar() const;

    private:
        void cambiarSprite();
        bool exploto;
        bool _terminoDeExplotar;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEBOLADEFUEGO_HPP