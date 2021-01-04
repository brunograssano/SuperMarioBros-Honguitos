#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_H

#include "ModificadorMario.h"

class MarioDeFuego : public ModificadorMario{
    public:
        void dispararFuego()override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_H
