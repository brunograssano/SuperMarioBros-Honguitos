
#include "DibujadorCreditos.hpp"


DibujadorCreditos::DibujadorCreditos(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla) {
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;
    this->ciclosDibujado = 0;
}

void DibujadorCreditos::dibujar(){
    dibujarRectanguloCreditos();
    dibujarTexto();
    this->ciclosDibujado++;
}

void DibujadorCreditos::dibujarTexto(){
    this->cargadorTexturas->obtenerTextura("Creditos");

    SDL_Rect recorteCreditos{0,ciclosDibujado/10, anchoRectanguloTransparente, altoRectanguloTransparente};

    SDL_Rect rectanguloTexto{xRectanguloTransparente, yRectanguloTransparente, anchoRectanguloTransparente, altoRectanguloTransparente };

    SDL_RenderCopy(renderizador, this->cargadorTexturas->obtenerTextura("Creditos"),
                   &recorteCreditos, &rectanguloTexto);
}

void DibujadorCreditos::dibujarRectanguloCreditos() {

    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 50;

    xRectanguloTransparente = 3*ancho_pantalla/4 - 200/2 - 25;
    yRectanguloTransparente = alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 150 - 25;
    anchoRectanguloTransparente = 250;
    altoRectanguloTransparente = (alto_puntosJugador + desfase_puntosJugador)*4+50;

    SDL_Rect rectanguloTransparente = {xRectanguloTransparente,yRectanguloTransparente,
                                       anchoRectanguloTransparente,altoRectanguloTransparente};
    SDL_SetRenderDrawBlendMode(renderizador, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderizador, 220, 220, 220, 120);
    SDL_RenderFillRect(renderizador, &rectanguloTransparente);
}