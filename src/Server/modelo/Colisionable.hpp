#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP

#include <map>
#include <string>
#include <typeinfo>
#include <tuple>

#include "src/Utils/colisiones/Colisionador.hpp"
#include "src/Utils/Utils.hpp"

using namespace std;

class Colisionable{

    public:
        typedef void(Colisionable::*FuncionDeColision)(void* contexto);
        typedef struct parFuncionColisionContexto {
            Colisionable::FuncionDeColision funcion;
            void* contexto;
        }parFuncionColisionContexto_t;

        virtual void chocarPorDerechaCon(Colisionable* colisionable);
        virtual void chocarPorIzquierdaCon(Colisionable* colisionable);
        virtual void chocarPorArribaCon(Colisionable* colisionable);
        virtual void chocarPorAbajoCon(Colisionable* colisionable);
        virtual string obtenerColisionID() = 0;
        virtual rectangulo_t obtenerRectangulo() = 0;

    protected:
        map<std::string, parFuncionColisionContexto_t> mapaColisionesPorDerecha;
        map<std::string, parFuncionColisionContexto_t> mapaColisionesPorIzquierda;
        map<std::string, parFuncionColisionContexto_t> mapaColisionesPorArriba;
        map<std::string, parFuncionColisionContexto_t> mapaColisionesPorAbajo;
        virtual void inicializarMapasDeColision() = 0;
        void ejecutarFuncionDeColision(map<std::string, parFuncionColisionContexto_t> mapaColisiones, Colisionable* colisionable);
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP