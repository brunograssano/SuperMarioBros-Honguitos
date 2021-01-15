#include "Camara.hpp"
#include "src/Server/sprites/SpriteMario.hpp"

const int ANCHO_SPRITE_PIXEL_MARIO = 16;

Camara::Camara(int alto_pantalla, int ancho_pantalla) {
    rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};
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

        if(jugador->estaConectado() && jugador->obtenerPosicionX() <= rectanguloCamara.x && jugador->estaVivo()) {
            sePuedeMoverLaCamara = false;
        }else if(jugador->estaConectado() && jugador->estaVivo()){
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

            jugador->actualizarMaximoX(rectanguloCamara.x);
            jugador->actualizarMinimoX(rectanguloCamara.x + rectanguloCamara.w - ANCHO_SPRITE_PIXEL_MARIO*2);
        }
    }

    if( rectanguloCamara.x < 0 ){
        rectanguloCamara.x = 0;
    }
}

SDL_Rect Camara::obtenerRectanguloCamara() {
    return rectanguloCamara;
}

bool Camara::estaEnRangoVisible(int posicionX) const{
    return (posicionX + ANCHO_RANGO > rectanguloCamara.x) &&
           (posicionX < rectanguloCamara.x + rectanguloCamara.w + ANCHO_RANGO);
}

bool Camara::estaEnRangoHelper(void *ptr, int x) {
    return (((Camara*) ptr)->estaEnRangoVisible(x));
}
