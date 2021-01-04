
#ifndef SRC_SERVER_MODELO_MONEDA_HPP_
#define SRC_SERVER_MODELO_MONEDA_HPP_

#include "../sprites/Sprite.hpp"
#include "../sprites/SpriteMoneda.hpp"
#include "PosicionFija.hpp"
#include "Posicion.hpp"
#include "src/Utils/Utils.hpp"

class Moneda{

    public:
        Moneda(int coordenadaX, int coordenadaY);
        ~Moneda();
        void actualizar();
        moneda_t serializar();
        int obtenerPosicionX();
        int obtenerPosicionY();

    private:
        Posicion* posicion;
        Sprite* sprite;
};


#endif /* SRC_SERVER_MODELO_MONEDA_HPP_ */
