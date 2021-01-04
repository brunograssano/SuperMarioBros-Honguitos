#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP

#include "Bloque.hpp"

class Sorpresa : public Bloque{
    public:
		Sorpresa(int coordenadaX, int coordenadaY);

		bloque_t serializar()override;

        ~Sorpresa() override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP
