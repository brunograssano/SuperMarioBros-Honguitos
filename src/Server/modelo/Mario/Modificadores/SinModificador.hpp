#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_HPP


#include "ModificadorMario.hpp"
#include "src/Server/modelo/Posicion.hpp"
#include "src/Server/modelo/Objetos/Disparo.hpp"
#include "src/Server/modelo/Objetos/Chispa.hpp"

class SinModificador : public ModificadorMario{
    const int MAX_CICLOS_PARA_CHISPEAR = 30;
    public:
        Disparo* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;
        void actualizar()override;

    private:
        int ciclosChispa = 0;
        bool yaPuedeChispear();
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_HPP
