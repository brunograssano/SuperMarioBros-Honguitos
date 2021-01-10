#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP


#include <VidaMario.h>
#include <src/Server/modelo/PosicionFija.hpp>
#include "src/Server/modelo/Objetos/Disparo.hpp"
#include "src/Server/modelo/Posicion.hpp"
class ModificadorMario {
    public:
        virtual ~ModificadorMario()= default;
        virtual Disparo* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) = 0;
        virtual ModificadorMario* perderVida(VidaMario* vidaMario)=0;
        virtual ModificadorMario* hacerseDeFuego();
        virtual void actualizar() = 0;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP
