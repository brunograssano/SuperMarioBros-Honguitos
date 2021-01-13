#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP

#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"

class Nada : public ObjetoFugaz{
    public:
        explicit Nada();
        void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        ~Nada() override;
        bool debeDesaparecer() override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP
