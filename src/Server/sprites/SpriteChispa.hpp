#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP

#include "Sprite.hpp"
#include "src/Utils/Constantes.hpp"
class SpriteChispa : public Sprite{
    const int CICLOS_PARA_CAMBIO = 5;
    public:
        explicit SpriteChispa(int direccion);
        ~SpriteChispa() override = default;
        SDL_Rect obtenerRectanguloActual() override;
        int obtenerEstadoActual() override;
        void actualizarSprite() override;
    private:
        void cambiarSprite();
        SDL_Rect estadosPosibles[4]{};
        int direccion;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITECHISPA_HPP
