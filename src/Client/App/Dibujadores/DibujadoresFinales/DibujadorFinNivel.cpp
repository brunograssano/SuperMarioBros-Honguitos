#include "DibujadorFinNivel.hpp"
const int ANCHO_IMAGEN_FONDO = 800;
const int ALTO_IMAGEN_FONDO = 800;

DibujadorFinNivel::DibujadorFinNivel(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla,JuegoCliente *juegoCliente){
    this->alto_pantalla = alto_pantalla;
    this->ancho_pantalla = ancho_pantalla;
    this->cargadorTexturas = cargadorTexturas;
    this->renderizador = renderizador;
    this->juegoCliente = juegoCliente;

    colores[-1] = {150, 150 , 150, 255}; // Gris.
    colores[0] = {230, 30 , 044, 255}; // Rojo.
    colores[1] = {69 , 230, 52 , 255}; // Verde.
    colores[2] = {179, 25 , 252, 255}; // Violeta.
    colores[3] = {76 , 225, 252, 255}; // Celeste.
    ciclosDibujado = 0;
}

void DibujadorFinNivel::dibujar(){
    SDL_RenderClear( renderizador );

    SDL_Rect rectanguloFondo = {0, 0, ANCHO_IMAGEN_FONDO, ALTO_IMAGEN_FONDO};
    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura("FondoNivelTerminado"), &rectanguloFondo, nullptr);

    dibujarTextoFinNivel();

    SDL_RenderPresent( renderizador );
    ciclosDibujado++;
    if(ciclosDibujado >= 200) {
        juegoCliente->hayQueMostrarPuntosDeNivel = false;
        ciclosDibujado = 0;
    }
}

void DibujadorFinNivel::dibujarTextoFinNivel(){

    std::stringstream textoFinNivel;
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

    std::stringstream puntosJugador;
    int corrimiento = 100;

    int alto_borde_puntos = (alto_puntosJugador+desfase_puntosJugador+5) * juegoCliente->obtenerJugadores().size();
    SDL_Rect borde_puntos = {ancho_pantalla/6,
                           alto_pantalla/2 + alto_puntosJugador - corrimiento,
                           4*ancho_pantalla/6,
                           alto_borde_puntos};

    SDL_SetRenderDrawColor(renderizador, 51, 51, 51, 100);
    SDL_RenderFillRect(renderizador, &borde_puntos);

    int textosDibujados = 1;
    int indiceJugador = 0;
    for (auto const& parIdJugador : juegoCliente->obtenerJugadores()) {

        podio_t podio = juegoCliente->obtenerPodioPuntosAcumulados();
        puntosJugador.str("");
        std::string nombreJugador = juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].nombreJugador;
        puntosJugador << "Puntos de " << nombreJugador << ": " << podio.puntosNivel[indiceJugador];

        cuadradoPuntos = {ancho_pantalla/6 + 50,
                          alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * textosDibujados - corrimiento,
                          ancho_puntosJugador,
                          alto_puntosJugador};
        cuadradoCorazon = {5*ancho_pantalla/6 - 50 - 20*3,
                           alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * textosDibujados - corrimiento,
                           20,
                           20 };

        for(int i = 0; i<juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].mario.vidas; i++){
            SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura("Corazon"), nullptr, &cuadradoCorazon);
            cuadradoCorazon.x += 25;
        }

        int idColor = podio.ids[indiceJugador];

        if (juegoCliente->obtenerJugadores()[podio.ids[indiceJugador]].mario.recorteImagen == MARIO_GRIS) {
            idColor = MARIO_GRIS;
        }
        renderizarTexto(cuadradoPuntos, puntosJugador.str(), colores[idColor]);
        textosDibujados++;
        indiceJugador++;
    }

    renderizarTexto(cuadradoFinNivel, textoFinNivel.str(), colorDefault);
}


