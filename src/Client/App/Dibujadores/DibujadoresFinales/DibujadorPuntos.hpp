
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORPUNTOS_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORPUNTOS_HPP

#include "src/Client/App/CargadorTexturas.hpp"
#include "src/Client/App/JuegoCliente/JuegoCliente.hpp"
#include "src/Client/App/Dibujadores/Dibujador.hpp"
#include "src/Client/App/Botones/BotonConTexto.hpp"


class DibujadorPuntos : public Dibujador{

    public:
        DibujadorPuntos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla, JuegoCliente* juegoCliente);
        ~DibujadorPuntos() override;
        void dibujar() override;
        void agregarEventoDeClick(SDL_Event eventoClick) override;
    private:
        JuegoCliente* juegoCliente;
        BotonConTexto* botonIzquierdo;
        BotonConTexto* botonDerecho;
        SDL_Event eventoMouse{};
        int nivelAMostrarPuntos;
        int alto_pantalla;
        int ancho_pantalla;
        void disminuirNivelAMostrarPuntos(int ultimoNivel);
        void renderizarTexto(SDL_Rect renderQuad, std::string textoAMostrar, SDL_Color color) override;
        void aumentarNivelAMostrarPuntos (int ultimoNivel);
        CargadorTexturas* cargadorTexturas;
        SDL_Renderer* renderizador;
        std::map<int, SDL_Color> colores;
        void dibujarPuntosTotales(JuegoCliente *juegoCliente);
        void dibujarPuntosDelNivel(JuegoCliente *juegoCliente);
        void dibujarRectanguloPuntos(int ancho_puntosJugador, int alto_puntosJugador, int desfase_puntosJugador);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORPUNTOS_HPP
