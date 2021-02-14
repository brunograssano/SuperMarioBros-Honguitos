#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SERIALIZABLE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SERIALIZABLE_HPP

#include "../../../Utils/Utils.hpp"

class Serializable {
    public:
        virtual ~Serializable() = default;
        virtual entidad_t serializar()= 0;
    protected:
        virtual entidad_t serializar(unsigned short x, unsigned short y,uint8_t recorteX,uint8_t recorteY,uint8_t tipo,bool espejado);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SERIALIZABLE_HPP
