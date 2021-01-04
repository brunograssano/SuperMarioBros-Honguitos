#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PLATAFORMA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PLATAFORMA_HPP

#include "Bloque.hpp"

class Plataforma : public Bloque {
    public:
        Plataforma()= default;

        void agregarBloque(Bloque* bloque);

        list<Bloque*> obtenerBloques();
        bloque_t serializar()override{return {0,0,0,0};};
        list<bloque_t> serializarPlataforma();

        ~Plataforma() override;

    private:
        list<Bloque*> bloques;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PLATAFORMA_HPP
