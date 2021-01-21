#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_POSICIONFIJA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_POSICIONFIJA_HPP

#include "Posicion.hpp"

class PosicionFija : public Posicion{

    public:

        PosicionFija(int coordenadaX,int coordenadaY) : Posicion(){
            this->posicionX=(float)coordenadaX;
            this->posicionY=(float)coordenadaY;
        }

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_POSICIONFIJA_HPP
