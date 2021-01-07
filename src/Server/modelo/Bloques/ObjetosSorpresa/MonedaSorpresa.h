#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_H


#include "ObjetoSorpresa.h"

class MonedaSorpresa : public ObjetoSorpresa{
    public:
        MonedaSorpresa();
        void usarse(Mario* mario)override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MONEDASORPRESA_H
