#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP

#include "ObjetosSorpresa/ObjetoSorpresa.hpp"
#include "Bloque.hpp"

class Sorpresa : public Bloque{
    public:
		Sorpresa(int coordenadaX, int coordenadaY);
        ObjetoSorpresa* colisionaronAbajo()override;
        std::string obtenerColisionID() override;
        void elevar(int y) override;
        ~Sorpresa() override;

    private:
        void inicializarMapasDeColision() override;
        static ObjetoSorpresa * obtenerObjetoSorpresa(int posicionBloque, int altoBloque);
        void usarse(void* pVoid);
        ObjetoSorpresa* objetoSorpresa;
        bool usado;
        bool entregado;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SORPRESA_HPP
