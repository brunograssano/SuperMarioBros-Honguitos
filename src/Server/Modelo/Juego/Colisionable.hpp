#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP

#include <map>
#include <string>
#include <typeinfo>
#include <tuple>

#include "src/Utils/colisiones/Colisionador.hpp"
#include "src/Utils/Utils.hpp"

class Colisionable{

    public:
        typedef void(Colisionable::*FuncionDeColision)(void* contexto);
        typedef struct parFuncionColisionContexto {
            Colisionable::FuncionDeColision funcion;
            void* contexto;
        }parFuncionColisionContexto_t;

        virtual ~Colisionable() = default;
        virtual void chocarPorDerechaCon(Colisionable* colisionable);
        virtual void chocarPorIzquierdaCon(Colisionable* colisionable);
        virtual void chocarPorArribaCon(Colisionable* colisionable);
        virtual void chocarPorAbajoCon(Colisionable* colisionable);
        virtual std::string obtenerColisionID() = 0;
        virtual rectangulo_t obtenerRectangulo() = 0;
        virtual bool debeColisionar() = 0;
    protected:
        std::map<std::string, parFuncionColisionContexto_t> mapaColisionesPorDerecha;
        std::map<std::string, parFuncionColisionContexto_t> mapaColisionesPorIzquierda;
        std::map<std::string, parFuncionColisionContexto_t> mapaColisionesPorArriba;
        std::map<std::string, parFuncionColisionContexto_t> mapaColisionesPorAbajo;
        virtual void inicializarMapasDeColision() = 0;
        void ejecutarFuncionDeColision(std::map<std::string, parFuncionColisionContexto_t> mapaColisiones, Colisionable* colisionable);
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP