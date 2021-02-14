#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_OBSERVADOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_OBSERVADOR_HPP

class Observable;

class Observador {
    public:
        virtual ~Observador() = default;
        virtual void actualizar(Observable* observable)=0;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_OBSERVADOR_HPP
