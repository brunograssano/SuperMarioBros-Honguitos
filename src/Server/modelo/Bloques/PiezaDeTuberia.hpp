#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PIEZADETUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PIEZADETUBERIA_HPP

#include "src/Server/modelo/Colisionable.hpp"
#include "src/Utils/Utils.hpp"

class PiezaDeTuberia : public Colisionable{
    public:
        PiezaDeTuberia(int posX, int posY, int w, int h);
        void elevar(int y);
        string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;
    private:
        void inicializarMapasDeColision() override;
        rectangulo_t rectangulo{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PIEZADETUBERIA_HPP
