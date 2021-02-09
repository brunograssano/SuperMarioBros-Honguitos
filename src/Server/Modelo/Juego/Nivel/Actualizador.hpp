#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ACTUALIZADOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ACTUALIZADOR_HPP

#include "src/Server/Modelo/Juego/Nivel/Bloques/Bloque.hpp"
#include "Moneda.hpp"

class Actualizador {
    public:
        void actualizar(std::list<Moneda*> *actualizables);
        void actualizar(std::list<ObjetoFugaz*> *actualizables);
        void actualizar(std::list<Bloque*> *actualizables);
    private:
        void sacarMonedasAgarradas(std::list<Moneda*> *monedas);
        void sacarObjetosFugaces(std::list<ObjetoFugaz*> *objetosFugaces);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ACTUALIZADOR_HPP
