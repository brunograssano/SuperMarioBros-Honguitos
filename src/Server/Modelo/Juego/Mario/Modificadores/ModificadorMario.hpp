#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP

class Mario;
#include "src/Server/Modelo/Juego/Posiciones/PosicionFija.hpp"
#include "src/Server/Modelo/Juego/Mario/VidaMario.hpp"
#include "src/Server/Modelo/Juego/Objetos/ObjetoFugaz.hpp"

class ModificadorMario {
    public:
        virtual ~ModificadorMario()= default;
        virtual ObjetoFugaz* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) = 0;
        virtual ModificadorMario* perderVida(VidaMario* vidaMario)=0;
        virtual ModificadorMario* hacerseDeFuego() = 0;
        virtual void actualizar() = 0;
        virtual bool puedeAgarrarFlor() = 0;
        virtual uint8_t serializar() = 0;
    protected:
        Mario* marioAsociado{};

};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MODIFICADORMARIO_HPP
