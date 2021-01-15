#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_HPP


#include "ModificadorMario.hpp"
#include "src/Server/modelo/Posicion.hpp"
#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/Objetos/Chispa.hpp"

class SinModificador : public ModificadorMario{

    public:
        explicit SinModificador(Mario* marioAsociado);
        ObjetoFugaz* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;
        void actualizar()override;
        ModificadorMario* hacerseDeFuego() override;
        bool puedeAgarrarFlor() override;

    private:
        int ciclosChispa = 0;
        bool yaPuedeChispear() const;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SINMODIFICADOR_HPP
