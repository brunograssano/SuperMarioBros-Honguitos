#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PLATAFORMA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PLATAFORMA_HPP

#include "src/Server/Modelo/Juego/Colisionable.hpp"

class Plataforma : public Colisionable{

    public:
        Plataforma(int comienzoPlataformaX,int finPlataformaX,int alto);
        ~Plataforma() override = default;
        rectangulo_t obtenerRectangulo() override;
        std::string obtenerColisionID() override;
        bool debeColisionar() override;

    private:
        void inicializarMapasDeColision() override;
        rectangulo_t rangoPlataforma{};

};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PLATAFORMA_HPP