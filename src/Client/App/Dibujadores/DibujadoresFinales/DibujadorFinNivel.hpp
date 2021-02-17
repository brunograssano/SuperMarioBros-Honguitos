#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORFINNIVEL_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORFINNIVEL_HPP

#include "src/Client/App/Dibujadores/Dibujador.hpp"
#include "src/Client/App/Dibujadores/Dibujador.hpp"
#include "src/Client/App/CargadorTexturas.hpp"
#include "src/Client/App/JuegoCliente/JuegoCliente.hpp"

class DibujadorFinNivel : public Dibujador{
    public:
        DibujadorFinNivel(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla,JuegoCliente *juegoCliente);
        void dibujar()override;
        ~DibujadorFinNivel() override= default;
    private:
        void dibujarTextoFinNivel();
        void dibujarPuntos(int indiceJugador);
        JuegoCliente *juegoCliente;
        std::map<int, SDL_Color> colores;
        int ciclosDibujado;
};

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORFINNIVEL_HPP
