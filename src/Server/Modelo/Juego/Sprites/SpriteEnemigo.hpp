#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEENEMIGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEENEMIGO_HPP

#include "Sprite.hpp"

class SpriteEnemigo : public Sprite{
    public:
        virtual void morir() = 0;
        virtual bool seMostroElTiempoSuficienteEnPantalla() = 0;
        bool debeEspejarse() const{
            return this->estaEspejado;
        }
        void espejar() {
            this->estaEspejado = !estaEspejado;
        }
    protected:
        bool estaEspejado;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SPRITEENEMIGO_HPP
