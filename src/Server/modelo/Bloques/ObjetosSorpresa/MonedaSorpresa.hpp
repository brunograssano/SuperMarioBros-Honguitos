#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP


#include "ObjetoSorpresa.hpp"

class MonedaSorpresa : public ObjetoSorpresa{
    public:
        MonedaSorpresa();
        void usarse(Mario* mario)override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_HPP
