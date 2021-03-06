#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_META_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_META_HPP


#include <list>
#include <map>
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"

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
        bool conectadosVivosPasaronMetaYDesconectadosNo(const std::map<int, Mario *> &jugadores);
        static bool todosDesconectados(const std::map<int, Mario *> &jugadores);
        static bool conectadosMuertosYDesconectadosVivos(const std::map<int, Mario *> &jugadores);
        std::list<Mario*> ganadores;
        int puntoBandera;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_META_HPP
