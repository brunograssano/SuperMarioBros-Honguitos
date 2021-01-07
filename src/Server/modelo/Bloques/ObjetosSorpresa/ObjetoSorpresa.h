#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_H


#include "src/Server/modelo/Mario/Mario.hpp"
#include "src/Server/modelo/Posicion.hpp"

class ObjetoSorpresa {
    public:
        virtual ~ObjetoSorpresa() = default;
        virtual void usarse(Mario* mario) {};
        virtual bool fueUsado(){return usado;}
    protected:
        bool usado;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBJETOSORPRESA_H
