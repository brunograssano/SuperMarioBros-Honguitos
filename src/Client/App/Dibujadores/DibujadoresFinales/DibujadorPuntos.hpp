
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORPUNTOS_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORPUNTOS_HPP

#include "src/Client/App/CargadorTexturas.hpp"
#include "src/Client/App/JuegoCliente/JuegoCliente.hpp"
#include "src/Client/App/Dibujadores/Dibujador.hpp"

class DibujadorPuntos{

    public:
        DibujadorPuntos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
        void dibujarPuntos(JuegoCliente* juegoCliente);
        void dibujarPuntosGameOver(JuegoCliente* juegoCliente);
        void disminuirNivelAMostrarPuntos(int ultimoNivel);
        void aumentarNivelAMostrarPuntos (int ultimoNivel);
        void renderizarTexto(SDL_Rect renderQuad, string textoAMostrar, SDL_Color color);
    private:
        int nivelAMostrarPuntos;
        int alto_pantalla;
        int ancho_pantalla;
        CargadorTexturas* cargadorTexturas;
        SDL_Renderer* renderizador;
        map<int, SDL_Color> colores;

        void dibujarPuntosTotales(JuegoCliente *juegoCliente);
        void dibujarPuntosDelNivel(JuegoCliente *juegoCliente);
        void dibujarPuntosTotalesGameOver(JuegoCliente *juegoCliente);
        void dibujarRectanguloPuntos(int ancho_puntosJugador, int alto_puntosJugador, int desfase_puntosJugador);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORPUNTOS_HPP
