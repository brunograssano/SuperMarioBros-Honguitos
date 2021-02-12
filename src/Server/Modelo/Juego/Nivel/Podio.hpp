#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PODIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PODIO_HPP

#include <vector>
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Utils/Observador.hpp"

class Podio: public Observador {
    public:
        Podio()=default;
        void recibirJugadores(const std::map<int, Mario*>& jugadores);
        void actualizar(Observable* observable) override;
        std::vector<std::pair<Mario*, int>> getPodioNivel();
        std::vector<std::pair<Mario*, int>>  getPodioTotal();
        ~Podio() override =default;
    private:
        std::vector<std::pair<Mario*, int>> puntajeTotal;
        std::vector<std::pair<Mario*, int>> puntajeParcial;
        std::vector<std::pair<Mario*, int>> puntajeNivelAnterior;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PODIO_HPP
