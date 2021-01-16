#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PODIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PODIO_HPP
#include <map>
#include <vector>
#include <Mario.hpp>
#include "src/Utils/Observador.hpp"

using namespace std;

class Podio: public Observador {
    public:
        Podio()=default;
        void recibirJugadores(map<int, Mario*> jugadores);
        void actualizar(Observable* observable) override;
        vector<pair<Mario*, int>> getPodioNivel();
        vector<pair<Mario*, int>>  getPodioTotal();
        ~Podio()=default;
    private:
        vector<pair<Mario*, int>> puntajeTotal;
        vector<pair<Mario*, int>> puntajeParcial;
        vector<pair<Mario*, int>> puntajeNivelAnterior;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PODIO_HPP
