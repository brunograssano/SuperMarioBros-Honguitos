#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SINSORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SINSORPRESA_HPP


#include "ObjetoSorpresa.hpp"

class SinSorpresa : public ObjetoSorpresa{
    public:
        SinSorpresa() {
            _debeDesaparecer = true;
        }
        efecto_t serializar() override {return {0, 0, 0, 0};}
        virtual void actualizar() override {}
        virtual int obtenerPosicionX() override {return 0;}
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SINSORPRESA_HPP
