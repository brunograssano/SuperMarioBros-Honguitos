#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_HPP


#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Server/Modelo/Juego/Objetos/ObjetoFugaz.hpp"
#include "src/Server/Modelo/Juego/Posiciones/Posicion.hpp"

class ObjetoSorpresa : public ObjetoFugaz{
    public:
        ~ObjetoSorpresa() override = default;
        virtual void usarse(Mario* mario) {};

        bool debeDesaparecer() override;
        entidad_t serializar() override = 0;
        void actualizar() override = 0;
        int obtenerPosicionX() override = 0;
        int tipoDeEfecto() override = 0;

        std::string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override = 0;
        bool debeColisionar() override = 0;
        virtual void sonar();

    protected:
        void inicializarMapasDeColision() override = 0;
        bool _debeDesaparecer;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_HPP
