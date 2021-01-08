#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP

#include "ModificadorMario.hpp"
#include "src/Server/modelo/Posicion.hpp"
#include "src/Server/modelo/Objetos/Disparo.hpp"
#include "src/Server/modelo/Objetos/BolaDeFuego.hpp"
class MarioDeFuego : public ModificadorMario{
    public:
        Disparo* dispararFuego(Posicion posicionManosMario)override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP
