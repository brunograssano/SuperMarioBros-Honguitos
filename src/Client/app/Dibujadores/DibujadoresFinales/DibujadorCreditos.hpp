
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORCREDITOS_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORCREDITOS_HPP


#include <src/Client/app/juegoCliente/JuegoCliente.hpp>
#include "src/Client/app/Dibujadores/Dibujador.hpp"

class DibujadorCreditos{

public:
    DibujadorCreditos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
    void dibujarCreditos();
private:
    int alto_pantalla;
    int ancho_pantalla;
    CargadorTexturas* cargadorTexturas;
    SDL_Renderer* renderizador;
    void dibujarRectanguloCreditos();
    void dibujarTexto();
    int ciclosDibujado = 0;
    int xRectanguloTransparente;
    int yRectanguloTransparente;
    int anchoRectanguloTransparente;
    int altoRectanguloTransparente;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_DIBUJADORCREDITOS_HPP
