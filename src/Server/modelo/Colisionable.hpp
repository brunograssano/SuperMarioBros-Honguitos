#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP

#include <map>
#include <string>
#include <typeinfo>
using namespace std;

class Colisionable{



    public:
        typedef void(Colisionable::*FuncionDeColision)();
        virtual void chocarPorDerechaCon(Colisionable* colisionable);
        virtual void chocarPorIzquierdaCon(Colisionable* colisionable);
        virtual void chocarPorArribaCon(Colisionable* colisionable);
        virtual void chocarPorAbajoCon(Colisionable* colisionable);
        virtual string obtenerColisionID() = 0;
    protected:
        map<std::string, Colisionable::FuncionDeColision> mapaColisionesPorDerecha;
        map<std::string, Colisionable::FuncionDeColision> mapaColisionesPorIzquierda;
        map<std::string, Colisionable::FuncionDeColision> mapaColisionesPorArriba;
        map<std::string, Colisionable::FuncionDeColision> mapaColisionesPorAbajo;
        virtual void inicializarMapasDeColision() = 0;
        void ejecutarFuncionDeColision(map<std::string , Colisionable::FuncionDeColision> mapaColisiones, Colisionable* colisionable);
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONABLE_HPP