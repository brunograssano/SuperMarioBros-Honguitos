#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_H


#include "ModificadorMario.h"

class SinModificador : public ModificadorMario{
    public:
        void dispararFuego()override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_H
