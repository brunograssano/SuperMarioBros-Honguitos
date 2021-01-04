#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_LADRILLO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_LADRILLO_HPP


#include "Bloque.hpp"

class Ladrillo : public Bloque {

    public:
        Ladrillo(int coordenadaX, int coordenadaY, int tipo);
        bloque_t serializar()override;
        ~Ladrillo() override;

    private:
        int tipoLadrillo;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_LADRILLO_HPP
