#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
#include "Sprite.hpp"

class SpriteChispa : public Sprite{

    public:
        explicit SpriteChispa(int direccion);
        ~SpriteChispa() override = default;
        void actualizarSprite() override;
        bool estaEspejado();
    private:
        void cambiarSprite();
        bool espejado;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
