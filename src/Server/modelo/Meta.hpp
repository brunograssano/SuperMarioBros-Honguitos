#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_META_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_META_HPP

#include "Mario/Mario.hpp"
#include <list>
#include <map>
#include "src/Utils/Constantes.hpp"
using namespace std;

#define RESTA_PUNTOS 500
#define MAX_PUNTOS RESTA_PUNTOS*MAX_CONEXIONES


class Meta {
    public:
        explicit Meta(int puntoBandera);
        void agregarSiPasoLaMeta(Mario* jugador);
        void sumarPuntos(int puntosExtra);
        bool todosEnLaMeta(const std::map<int, Mario *>& map);
        ~Meta();
private:
        bool estaEnLaMeta(Mario* jugador) const;
        bool yaLLegoALaMeta(Mario* jugador);
        list<Mario*> ganadores;
        int puntoBandera;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_META_HPP
