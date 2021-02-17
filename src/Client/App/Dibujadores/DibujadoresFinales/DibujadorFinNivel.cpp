#include <unistd.h>
#include "src/Utils/Constantes.hpp"
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
    sleep(TIEMPO_ESPERA_GAME_LOOP);
    juegoCliente->dejarDeMostrarPuntosNivel();
}

void DibujadorFinNivel::dibujarTextoFinNivel(){

    std::stringstream textoFinNivel;
    textoFinNivel.str("");
    int nivelAnterior = juegoCliente->obtenerMundoActual() - 1;
    textoFinNivel << "Fin del Nivel " << nivelAnterior;

    int ancho_textoFinNivel = 400;
    int alto_textoFinNivel = 60;

    SDL_Rect cuadradoFinNivel = {ancho_pantalla/2 -ancho_textoFinNivel/2,
                            alto_pantalla/2 - alto_textoFinNivel/2 - 160,
                            ancho_textoFinNivel,
                            alto_textoFinNivel};

    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 20;

    std::stringstream puntosJugador;
    int corrimiento = 100;

    int alto_borde_puntos = (alto_puntosJugador+desfase_puntosJugador+5) * juegoCliente->obtenerJugadores().size();
    SDL_Rect borde_puntos = {ancho_pantalla/6,
                           alto_pantalla/2 + alto_puntosJugador - corrimiento,
                           4*ancho_pantalla/6,
                           alto_borde_puntos};

    SDL_SetRenderDrawColor(renderizador, 51, 51, 51, 100);
    SDL_RenderFillRect(renderizador, &borde_puntos);

    int cantidadJugadores = juegoCliente->obtenerJugadores().size();

    for (int idJugador = 0; idJugador < cantidadJugadores; idJugador++) {
        dibujarPuntos(idJugador);
    }

    renderizarTexto(cuadradoFinNivel, textoFinNivel.str(), colorDefault);
}

void DibujadorFinNivel::dibujarPuntos(int idJugador){
    int ultimoNivel = juegoCliente->obtenerNivelesJugados()-1;
    std::map<int, jugador> jugadores = juegoCliente->obtenerJugadores();
    int cantidadJugadores = jugadores.size();
    int offsetPuntos = 0;

    int ancho_puntosJugador = 50;
    int alto_puntosJugador = 30;
    int desfase_puntosJugador = 20;
    int corrimiento = 100;

    for(int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++){
        jugador_t jugador = jugadores[indiceJugador];
        std::string nombreJugador = jugador.nombreJugador;
        SDL_Rect cuadradoNombre = {ancho_pantalla/6 + 50,
                                   alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * (indiceJugador+1) - corrimiento,
                                   ancho_puntosJugador,
                                   alto_puntosJugador};
        int idColor = indiceJugador;

        if (jugador.mario.recorteImagen == MARIO_GRIS) {
            idColor = MARIO_GRIS;
        }
        renderizarTexto(cuadradoNombre, nombreJugador, colores[idColor]);

    }

    for(int indiceNivel = 1; indiceNivel <= ultimoNivel; indiceNivel++){
        podio_t podio = juegoCliente->obtenerPodios().at(indiceNivel);
        std::string nivel = "Nivel "+ std::to_string(podio.nivel);
        SDL_Rect cuadradoNivel = {ancho_pantalla/6 + 150 + offsetPuntos,
                                  alto_pantalla/2 + (alto_puntosJugador) - corrimiento - 50,
                                  ancho_puntosJugador,
                                  50};
        renderizarTexto(cuadradoNivel, nivel, colores[MARIO_GRIS]);

        for(int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++){
            int id = podio.ids[indiceJugador];
            if(id == idJugador){
                SDL_Rect cuadradoPuntos = {ancho_pantalla/6 + 150 + offsetPuntos,
                                           alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * (idJugador+1) - corrimiento,
                                              ancho_puntosJugador,
                                              alto_puntosJugador};

                jugador_t jugador = jugadores[idJugador];

                std::stringstream puntosJugador;
                puntosJugador.str("");
                puntosJugador << podio.puntosNivel[indiceJugador];

                int idColor = idJugador;

                if (jugador.mario.recorteImagen == MARIO_GRIS) {
                    idColor = MARIO_GRIS;
                }
                renderizarTexto(cuadradoPuntos, puntosJugador.str(), colores[idColor]);
                offsetPuntos += 70;
            }
        }
    }

    podio_t podioA = juegoCliente->obtenerPodioPuntosAcumulados();
    std::string acum = "Total";
    SDL_Rect cuadradoAcum = {ancho_pantalla/6 + 150 + 330,
                              alto_pantalla/2 + (alto_puntosJugador) - corrimiento - 50,
                              ancho_puntosJugador,
                              50};
    renderizarTexto(cuadradoAcum, acum, colores[MARIO_GRIS]);

    offsetPuntos = 0;
    for(int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++){
        int id = podioA.ids[indiceJugador];
        if(id == idJugador){
            SDL_Rect cuadradoPuntos = {ancho_pantalla/6 + 150 + 330,
                                       alto_pantalla/2 + (alto_puntosJugador+desfase_puntosJugador) * (idJugador + 1) - corrimiento,
                                       ancho_puntosJugador,
                                       50};

            jugador_t jugador = jugadores[idJugador];

            std::stringstream puntosJugador;
            puntosJugador.str("");
            puntosJugador << podioA.puntosNivel[indiceJugador];


            int idColor = idJugador;

            if (jugador.mario.recorteImagen == MARIO_GRIS) {
                idColor = MARIO_GRIS;
            }
            renderizarTexto(cuadradoPuntos, puntosJugador.str(), colores[idColor]);
            offsetPuntos += 70;
        }
    }

}