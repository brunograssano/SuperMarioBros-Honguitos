#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP

#include "src/Server/Modelo/Juego/Objetos/ObjetoFugaz.hpp"
#include "src/Utils/Constantes.hpp"

class Nada : public ObjetoFugaz{
    public:
        explicit Nada();
        void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        int tipoDeEfecto() override;
        ~Nada() override;
        bool debeDesaparecer() override;
        string obtenerColisionID() override {return  COLISION_ID_NADA;}
        rectangulo_t obtenerRectangulo() override{return {0,0,0,0,0,0};}
        bool debeColisionar() override {return false;}

    private:
        void inicializarMapasDeColision() override {}

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_NADA_HPP
