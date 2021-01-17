#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SINSORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SINSORPRESA_HPP


#include "ObjetoSorpresa.hpp"

class SinSorpresa : public ObjetoSorpresa{
    public:
        SinSorpresa() {
            _debeDesaparecer = true;
        }
        efecto_t serializar() override {return {0, 0, 0, 0};}
        void actualizar() override {}
        int obtenerPosicionX() override {return 0;}
        string obtenerColisionID() override {return  COLISION_ID_NADA;}
        rectangulo_t obtenerRectangulo() override{return {0,0,0,0,0,0};}
        bool debeColisionar() override {return false;}

private:
        void inicializarMapasDeColision() override {}
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SINSORPRESA_HPP
