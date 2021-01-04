#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_H


#include <VidaMario.h>

class ModificadorMario {
    public:
        virtual ~ModificadorMario()= default;
        virtual void dispararFuego() = 0; //agregar lo que se necesite para los calculos
        virtual ModificadorMario* perderVida(VidaMario* vidaMario)=0;
        virtual ModificadorMario* hacerseDeFuego();
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_H
