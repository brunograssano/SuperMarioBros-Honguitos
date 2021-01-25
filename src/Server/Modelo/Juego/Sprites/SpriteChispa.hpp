#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
#include "Sprite.hpp"
#include "src/Utils/Constantes.hpp"

class SpriteChispa : public Sprite{

    public:
        explicit SpriteChispa(int direccion);
        ~SpriteChispa() override = default;
        int obtenerEstadoActual() override;
        void actualizarSprite() override;
    private:
        void cambiarSprite();
        int direccion;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
