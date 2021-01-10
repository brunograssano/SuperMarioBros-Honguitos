#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP

#include "ModificadorMario.hpp"
#include "src/Server/modelo/Posicion.hpp"
#include "src/Server/modelo/Objetos/Disparo.hpp"
#include "src/Server/modelo/Objetos/BolaDeFuego.hpp"
class MarioDeFuego : public ModificadorMario{
    const int MAX_CICLOS_PARA_DISPARAR = 70;
    public:
        Disparo* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;
        void actualizar()override;

    private:
        int ciclosDisparo = 0;
        bool yaPuedeDisparar();
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP
