#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_HPP


#include "src/Server/modelo/Mario/Mario.hpp"
#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/Posicion.hpp"

class ObjetoSorpresa : public ObjetoFugaz{
    public:
        virtual ~ObjetoSorpresa() = default;
        virtual void usarse(Mario* mario) {};

        bool debeDesaparecer() override;
        virtual efecto_t serializar() override = 0;
        virtual void actualizar() override = 0;
        virtual int obtenerPosicionX() override = 0;

    protected:
        bool _debeDesaparecer;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_HPP
