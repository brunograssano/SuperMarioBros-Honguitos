#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP

#include "src/Server/modelo/Objetos/Disparo.hpp"

class Nada : public Disparo{
    public:
        explicit Nada();
        void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        ~Nada() override;
        bool debeDesaparecer() override;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP
