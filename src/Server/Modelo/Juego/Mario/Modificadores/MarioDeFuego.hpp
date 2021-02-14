#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP

#include "ModificadorMario.hpp"

class MarioDeFuego : public ModificadorMario{
    public:
        explicit MarioDeFuego(Mario* marioAsociado);
        ObjetoFugaz* dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) override;
        ModificadorMario* perderVida(VidaMario* vidaMario)override;
        void actualizar()override;
        ModificadorMario* hacerseDeFuego() override;
        bool puedeAgarrarFlor() override;
        uint8_t serializar() override;

    private:
        int ciclosDisparo = 0;
        int ciclosChispa = 0;
        bool yaPuedeDisparar() const;
        bool yaPuedeChispear() const;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MARIODEFUEGO_HPP
