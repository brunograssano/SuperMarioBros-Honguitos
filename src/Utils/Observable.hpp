#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBSERVABLE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBSERVABLE_HPP

#include <list>

class Observador;

class Observable {
    public:
        virtual ~Observable() = default;
        virtual void agregar(Observador* observador);
        virtual void eliminar(Observador* observador);
        virtual void notificar();
    private:
        std::list<Observador*> observadores;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBSERVABLE_HPP
