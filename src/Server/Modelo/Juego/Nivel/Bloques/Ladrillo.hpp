#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_LADRILLO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_LADRILLO_HPP


#include "Bloque.hpp"

class Ladrillo : public Bloque {

    public:
        Ladrillo(int coordenadaX, int coordenadaY, int tipo);
        std::string obtenerColisionID() override;
        ~Ladrillo() override;
    private:
        void romperse(void* ptr = nullptr);
        void inicializarMapasDeColision() override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_LADRILLO_HPP
