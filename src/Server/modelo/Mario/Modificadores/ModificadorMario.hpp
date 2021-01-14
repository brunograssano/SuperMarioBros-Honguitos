#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP


#include <VidaMario.hpp>
#include <src/Server/modelo/PosicionFija.hpp>
#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/Posicion.hpp"
class ModificadorMario {
    public:
        virtual ~ModificadorMario()= default;
        virtual ObjetoFugaz* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) = 0;
        virtual ModificadorMario* perderVida(VidaMario* vidaMario)=0;
        virtual ModificadorMario* hacerseDeFuego() = 0;
        virtual void actualizar() = 0;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP
