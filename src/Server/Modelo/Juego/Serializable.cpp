#include "Serializable.hpp"

entidad_t Serializable::serializar(unsigned short x, unsigned short y,uint8_t recorteX,uint8_t recorteY,uint8_t tipo,bool espejado) {
    entidad_t serializable = {0, 0, 0, 0,0,false};
    serializable.x = x;
    serializable.y = y;
    serializable.recorteX = recorteX;
    serializable.recorteY = recorteY;
    serializable.tipo = tipo;
    serializable.espejado = espejado;
    return serializable;
}
