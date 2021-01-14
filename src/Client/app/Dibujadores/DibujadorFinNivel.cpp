#include "DibujadorFinNivel.hpp"
const int ANCHO_IMAGEN_FONDO = 800;
const int ALTO_IMAGEN_FONDO = 800;

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

    SDL_Rect rectanguloFondo = {0, 0, ANCHO_IMAGEN_FONDO, ALTO_IMAGEN_FONDO};
    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura("FondoNivelTerminado"), &rectanguloFondo, nullptr);

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

    SDL_Rect cuadradoFinNivel = {ancho_pantalla/2 -ancho_textoFinNivel/2,
                            alto_pantalla/2 - alto_textoFinNivel/2 - 130,
                            ancho_textoFinNivel,
                            alto_textoFinNivel};

    int ancho_puntosJugador = 200;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 20;

    SDL_Rect cuadradoPuntos;
    SDL_Rect cuadradoCorazon;

    stringstream puntosJugador;
    int corrimientoCorazon = 200;
    int corrimiento = 100;

    int alto_borde_puntos = (alto_puntosJugador+desfase_puntosJugador+5) * juegoCliente->obtenerJugadores().size();
    SDL_Rect borde_puntos = {ancho_pantalla/3 - ancho_puntosJugador/2 - 30,
                           alto_pantalla/2 + alto_puntosJugador - corrimiento,
                           4*ancho_pantalla/6,
                           alto_borde_puntos};

    SDL_SetRenderDrawColor(renderizador, 51, 51, 51, 100);
    SDL_RenderFillRect(renderizador, &borde_puntos);

    int textosDibujados = 1;
    for (auto const& parIdJugador : juegoCliente->obtenerJugadores()){
        puntosJugador.str("");
        puntosJugador << "Puntos de "<< parIdJugador.second.nombreJugador <<": " << parIdJugador.second.puntos;

        cuadradoPuntos = {ancho_pantalla/3 - ancho_puntosJugador/2,
                          alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * textosDibujados - corrimiento,
                          ancho_puntosJugador,
                          alto_puntosJugador};
        cuadradoCorazon = {ancho_pantalla/3 - ancho_puntosJugador/2 + ancho_puntosJugador + corrimientoCorazon,
                           alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * textosDibujados - corrimiento,
                           20,
                           20 };

        for(int i = 0; i<parIdJugador.second.mario.vidas; i++){
            SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura("Corazon"), nullptr, &cuadradoCorazon);
            cuadradoCorazon.x += 25;
        }

        int idColor = parIdJugador.first;

        if(parIdJugador.second.mario.recorteImagen == MARIO_GRIS){
            idColor = MARIO_GRIS;
        }
        renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str(), colores[idColor]);
        textosDibujados++;
    }

    renderizarTexto(cuadradoFinNivel, textoFinNivel.str().c_str(), colorDefault);
}


