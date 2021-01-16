#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_POZO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_POZO_HPP

#include "Bloque.hpp"

class Pozo {

public:
    Pozo(int posicionX, int tipo, int fondo);
    unsigned short obtenerPosicionX() const;

    pozo_t serializar();

private:
    unsigned short posicionX;
    uint8_t tipo;
    uint8_t fondo;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_POZO_HPP
