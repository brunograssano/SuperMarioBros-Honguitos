#include "DibujadorFinNivel.hpp"
const int ANCHO_FONDO = 8177;

DibujadorFinNivel::DibujadorFinNivel(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;

    colores[-1] = {150, 150 , 150, 255}; // Gris.
    colores[0] = {230, 30 , 044, 255}; // Rojo.
    colores[1] = {69 , 230, 52 , 255}; // Verde.
    colores[2] = {179, 25 , 252, 255}; // Violeta.
    colores[3] = {76 , 225, 252, 255}; // Celeste.
    ciclosDibujado = 0;
}


void DibujadorFinNivel::dibujar(JuegoCliente* juegoCliente){
    SDL_RenderClear( renderizador );

    SDL_Rect rectanguloCamara = {(ANCHO_FONDO - ancho_pantalla), 0, alto_pantalla, ancho_pantalla};
    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), &rectanguloCamara, nullptr);

    dibujarTextoFinNivel(juegoCliente);
    SDL_RenderPresent( renderizador );
    ciclosDibujado++;
    if(ciclosDibujado >= 200) {
        juegoCliente->hayQueMostrarPuntosDeNivel = false;
        ciclosDibujado = 0;
    }
}

void DibujadorFinNivel::dibujarTextoFinNivel(JuegoCliente* juegoCliente){

    stringstream textoFinNivel;
    textoFinNivel.str("");
    int nivelAnterior = juegoCliente->obtenerMundoActual() - 1;
    textoFinNivel << "Fin del Nivel " << nivelAnterior;

    int ancho_textoFinNivel = 400;
    int alto_textoFinNivel = 60;

    SDL_Rect cuadradoFin = {ancho_pantalla/2 -ancho_textoFinNivel/2,
                            alto_pantalla/2 - alto_textoFinNivel/2 - 100,
                            ancho_textoFinNivel,
                            alto_textoFinNivel};

    int ancho_puntosJugador = 200;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 50;
    SDL_Rect cuadradoPuntos;

    stringstream puntosJugador;

    for (auto const& parIdJugador : juegoCliente->obtenerJugadores()){
        puntosJugador.str("");
        puntosJugador << "Puntos de "<< parIdJugador.second.nombreJugador <<": " << parIdJugador.second.puntos;

        cuadradoPuntos = {ancho_pantalla/2 -ancho_puntosJugador/2,
                          alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador - 100,
                          ancho_puntosJugador,
                          alto_puntosJugador};
        int idColor = parIdJugador.first;

        if(parIdJugador.second.mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }
        renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str(), colores[idColor]);
        desfase_puntosJugador +=40;
    }

    renderizarTexto(cuadradoFin, textoFinNivel.str().c_str(), colorDefault);
}

