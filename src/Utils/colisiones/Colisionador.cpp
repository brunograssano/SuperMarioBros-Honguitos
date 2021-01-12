#include "Colisionador.hpp"
#include "src/Server/modelo/Colisionable.hpp"
#include "SDL2/SDL.h"

int tipoDeChoque(rectangulo_t rect1, rectangulo_t rect2) {

    bool derecha = rect1.x1 > rect2.x1 && rect1.x1 < rect2.x2;
    bool izquierda = rect1.x2 > rect2.x1 && rect1.x2 < rect2.x2;
    bool arriba = rect1.y1 > rect2.y1 && rect1.y1 < rect2.y2;
    bool abajo = rect1.y2 > rect2.y1 && rect1.y2 < rect2.y2;

    SDL_Rect interseccion;
    SDL_Rect A = {rect1.x1, rect1.y1, rect1.w, rect1.h};
    SDL_Rect B = {rect2.x1, rect2.y1, rect2.w, rect2.h};

    bool hayInterseccion = (bool)SDL_IntersectRect(&A, &B, &interseccion);

    if(!hayInterseccion)
        return SIN_CHOQUE;

    if(interseccion.h > interseccion.w){
        //x
        if(derecha && izquierda){
            return PRIMERO_DERECHA_SEGUNDO_IZQUIERDA;
        }else if(derecha && !izquierda){
            return PRIMERO_IZQUIERDA_SEGUNDO_DERECHA;
        }else if(!derecha && izquierda){
            return PRIMERO_DERECHA_SEGUNDO_IZQUIERDA;
        }

    }else{
        //y
        if(arriba && abajo){
            return PRIMERO_ARRIBA_SEGUNDO_ABAJO;
        }else if(arriba && !abajo){
            return PRIMERO_ABAJO_SEGUNDO_ARRIBA;
        }else if(!arriba && abajo){
            return PRIMERO_ARRIBA_SEGUNDO_ABAJO;
        }
    }

    return SIN_CHOQUE;
}

void chocar(Colisionable* colisionable1, Colisionable* colisionable2) {
    rectangulo_t rectangulo1 = colisionable1->obtenerRectangulo();
    rectangulo_t rectangulo2 = colisionable2->obtenerRectangulo();

    switch(tipoDeChoque(rectangulo1, rectangulo2)){

        case PRIMERO_DERECHA_SEGUNDO_IZQUIERDA:
            colisionable1->chocarPorDerechaCon(colisionable2);
            colisionable2->chocarPorIzquierdaCon(colisionable1);
            break;
        case PRIMERO_IZQUIERDA_SEGUNDO_DERECHA:
            colisionable1->chocarPorIzquierdaCon(colisionable2);
            colisionable2->chocarPorDerechaCon(colisionable1);
            break;
        case PRIMERO_ARRIBA_SEGUNDO_ABAJO:
            colisionable1->chocarPorArribaCon(colisionable2);
            colisionable2->chocarPorAbajoCon(colisionable1);
            break;
        case PRIMERO_ABAJO_SEGUNDO_ARRIBA:
            colisionable1->chocarPorAbajoCon(colisionable2);
            colisionable2->chocarPorArribaCon(colisionable1);
            break;
        case SIN_CHOQUE:
        default:
            break;
    }

}