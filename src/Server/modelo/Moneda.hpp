#ifndef SRC_SERVER_MODELO_MONEDA_HPP_
#define SRC_SERVER_MODELO_MONEDA_HPP_

#include "../sprites/SpriteMoneda.hpp"
#include "Posicion.hpp"
#include "src/Utils/Utils.hpp"
#include "src/Server/modelo/Colisionable.hpp"
#include "src/Utils/Constantes.hpp"

class Moneda : public Colisionable{

    public:
        Moneda(int coordenadaX, int coordenadaY);
        ~Moneda() override = default;
        void actualizar();
        moneda_t serializar();
        int obtenerPosicionX();
        int obtenerPosicionY();
        void elevar(int y);
        string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;
        bool fueAgarrada() const;
    private:
        void inicializarMapasDeColision() override;
        void agarrar(void* ptr = nullptr);
        Posicion posicion;
        SpriteMoneda sprite;
        bool agarrada;
};


#endif /* SRC_SERVER_MODELO_MONEDA_HPP_ */
