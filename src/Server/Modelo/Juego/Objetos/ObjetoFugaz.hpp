#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOFUGAZ_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOFUGAZ_HPP

#include "src/Server/Modelo/Juego/Actualizable.hpp"
#include "src/Server/Modelo/Juego/Serializable.hpp"
#include "src/Server/Modelo/Juego/Colisionable.hpp"

class ObjetoFugaz : public Colisionable, public Serializable,Actualizable{
    public:
        virtual bool debeDesaparecer() = 0;
        virtual entidad_t serializar() = 0;
        virtual void actualizar() = 0;
        virtual int obtenerPosicionX() = 0;
        virtual int tipoDeEfecto() = 0;
        ~ObjetoFugaz() override = default;

        std::string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override = 0;
        bool debeColisionar() override = 0;

    protected:
        void inicializarMapasDeColision() override = 0;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOFUGAZ_HPP