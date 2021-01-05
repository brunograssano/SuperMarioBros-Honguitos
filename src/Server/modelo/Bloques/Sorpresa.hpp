#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP

#include "ObjetosSorpresa/ObjetoSorpresa.h"
#include "Bloque.hpp"

class Sorpresa : public Bloque{
    public:
		Sorpresa(int coordenadaX, int coordenadaY);
        ObjetoSorpresa* colisionaronAbajo()override;
        ~Sorpresa() override;

    private:
        static ObjetoSorpresa * obtenerObjetoSorpresa(int posicionBloque, int altoBloque);
        ObjetoSorpresa* objetoSorpresa;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP
