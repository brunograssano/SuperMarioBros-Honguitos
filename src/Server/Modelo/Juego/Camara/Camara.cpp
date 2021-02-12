#include "Camara.hpp"
#include "src/Utils/colisiones/Colisionador.hpp"
#include "src/Utils/Constantes.hpp"

const int ANCHO_SPRITE_PIXEL_MARIO = 16;

Camara::Camara(int alto_pantalla, int ancho_pantalla) {
    rectanguloCamara = { 0, ancho_pantalla, 0, alto_pantalla, alto_pantalla, ancho_pantalla};
}

void Camara::reiniciar(){
    rectanguloCamara.x1 = 0;
    rectanguloCamara.y1 = 0;
    rectanguloCamara.x2 = rectanguloCamara.w;
    rectanguloCamara.y2 = rectanguloCamara.h;
}

void Camara::moverCamara(const std::map<int,Mario*>& jugadores) {
    int posicionDelJugadorMasALaDerecha = 0;
    int posicionDelJugadorMasALaIzquierda = ANCHO_FONDO;

    bool sePuedeMoverLaCamara = true;

    for(auto const& parClaveJugador: jugadores){
        auto jugador = parClaveJugador.second;

        if(jugador->estaConectado() && jugador->obtenerPosicionX() <= rectanguloCamara.x1 && jugador->estaVivo()) {
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

    bool unJugadorEstaDelLadoDerechoDeLaPantalla = posicionDelJugadorMasALaDerecha > rectanguloCamara.x1 + (rectanguloCamara.w)/2;

    if(sePuedeMoverLaCamara && unJugadorEstaDelLadoDerechoDeLaPantalla){
        //MOVER CAMARA
        if(posicionDelJugadorMasALaIzquierda < posicionDelJugadorMasALaDerecha - rectanguloCamara.w/2){
            rectanguloCamara.x1 = posicionDelJugadorMasALaIzquierda;
        }else{
            rectanguloCamara.x1 = posicionDelJugadorMasALaDerecha - rectanguloCamara.w/2;
        }

        if( rectanguloCamara.x1 > ANCHO_FONDO - rectanguloCamara.w){
            rectanguloCamara.x1 = ANCHO_FONDO - rectanguloCamara.w;
        }

        rectanguloCamara.x2 = rectanguloCamara.x1 + rectanguloCamara.w;

        for(auto const& parClaveJugador: jugadores){
            auto jugador = parClaveJugador.second;
            if((!jugador->estaConectado()) && (jugador->obtenerPosicionX()<=rectanguloCamara.x1)){
                jugador->serArrastrado(rectanguloCamara.x1-jugador->obtenerPosicionX());
            }
        }
    }

    for(auto const& parClaveJugador : jugadores){
        auto jugador = parClaveJugador.second;
        jugador->actualizarMaximoX(rectanguloCamara.x1);
        jugador->actualizarMinimoX(rectanguloCamara.x1 + rectanguloCamara.w - ANCHO_SPRITE_PIXEL_MARIO*2);
    }

    if( rectanguloCamara.x1 < 0 ){
        rectanguloCamara.x1 = 0;
        rectanguloCamara.x2 = rectanguloCamara.w;
    }
}

rectangulo_t Camara::obtenerRectanguloCamara() {
    return rectanguloCamara;
}

bool Camara::estaEnRangoVisible(rectangulo_t rect) const{
    return colisionan(rectanguloCamara, rect);
}

bool Camara::estaEnRangoHelper(void *ptr, rectangulo_t rect) {
    return (((Camara*) ptr)->estaEnRangoVisible(rect));
}
