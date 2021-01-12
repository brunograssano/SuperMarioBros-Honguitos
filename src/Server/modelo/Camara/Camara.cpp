#include "Camara.hpp"
#include "src/Server/sprites/SpriteMario.hpp"

Camara::Camara(int alto_pantalla, int ancho_pantalla) {
    rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};
}

Camara::~Camara() {

}

void Camara::reiniciar(){
    rectanguloCamara.x = 0;
    rectanguloCamara.y = 0;
}

void Camara::moverCamara(const map<int,Mario*>& jugadores) {
    int posicionDelJugadorMasALaDerecha = 0;
    int posicionDelJugadorMasALaIzquierda = ANCHO_FONDO;

    bool sePuedeMoverLaCamara = true;
    Mario* jugador;

    for(auto const& parClaveJugador: jugadores){
        jugador = parClaveJugador.second;

        if(jugador->estaConectado() && jugador->obtenerPosicionX() <= rectanguloCamara.x) {
            sePuedeMoverLaCamara = false;
        }else if(jugador->estaConectado()){
            if(jugador->obtenerPosicionX() > posicionDelJugadorMasALaDerecha){
                posicionDelJugadorMasALaDerecha = jugador->obtenerPosicionX();
            }
            if(jugador->obtenerPosicionX() < posicionDelJugadorMasALaIzquierda){
                posicionDelJugadorMasALaIzquierda = jugador->obtenerPosicionX();
            }
        }
    }

    bool unJugadorEstaDelLadoDerechoDeLaPantalla = posicionDelJugadorMasALaDerecha > rectanguloCamara.x + (rectanguloCamara.w)/2;

    if(sePuedeMoverLaCamara && unJugadorEstaDelLadoDerechoDeLaPantalla){
        //MOVER CAMARA
        if(posicionDelJugadorMasALaIzquierda < posicionDelJugadorMasALaDerecha - rectanguloCamara.w/2){
            rectanguloCamara.x = posicionDelJugadorMasALaIzquierda;
        }else{
            rectanguloCamara.x = posicionDelJugadorMasALaDerecha - rectanguloCamara.w/2;
        }

        if( rectanguloCamara.x > ANCHO_FONDO - rectanguloCamara.w){
            rectanguloCamara.x = ANCHO_FONDO - rectanguloCamara.w;
        }

        for(auto const& parClaveJugador: jugadores){
            jugador = parClaveJugador.second;
            if((!jugador->estaConectado()) && (jugador->obtenerPosicionX()<=rectanguloCamara.x)){
                jugador->serArrastrado(rectanguloCamara.x-jugador->obtenerPosicionX());
            }

            int anchoJugador = jugador->obtenerSpite()->obtenerRectanguloActual().w;
            jugador->actualizarMaximoX(rectanguloCamara.x);
            jugador->actualizarMinimoX(rectanguloCamara.x + rectanguloCamara.w - anchoJugador*2);
        }
    }

    if( rectanguloCamara.x < 0 ){
        rectanguloCamara.x = 0;
    }
}

SDL_Rect Camara::obtenerRectanguloCamara() {
    return rectanguloCamara;
}

bool Camara::estaEnRangoVisible(int posicionX){
    return (posicionX + ANCHO_RANGO > rectanguloCamara.x) &&
           (posicionX < rectanguloCamara.x + rectanguloCamara.w + ANCHO_RANGO);
}