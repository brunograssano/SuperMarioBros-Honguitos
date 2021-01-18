#include "Tuberia.hpp"
#include "src/Utils/Constantes.hpp"

#define PIXEL_DESFASE 2

Tuberia::Tuberia(int posX, int tipo, int color) {
    posicion = PosicionFija(posX, 0);
    this->tipo = tipo;
    this->color = color;
    crearColisionables(posX, tipo);
}

void Tuberia::crearColisionables(int x, int tipo) {
    if(tipo == TUBERIA_CHICA){
        piezas.push_back(new PiezaDeTuberia(x, 0, ANCHO_TUBERIA_CHICA, ALTO_TUBERIA_CHICA));
        dimensiones = {x, 0, ANCHO_TUBERIA_CHICA, ALTO_TUBERIA_CHICA}; //todo: migrar a rectangulo_t
    }else{
        piezas.push_back(new PiezaDeTuberia(x, 0, ANCHO_TUBERIA_CHICA, ALTO_TUBERIA_CHICA - PIXEL_DESFASE));
        piezas.push_back(new PiezaDeTuberia(x + ANCHO_TUBERIA_CHICA, 0, ANCHO_TUBERIA_CHICA - 2*PIXEL_DESFASE, ALTO_TUBERIA_GRANDE));
        dimensiones = {x, 0, ANCHO_TUBERIA_GRANDE, ALTO_TUBERIA_GRANDE}; //todo: migrar a rectangulo_t
    }
}


bool Tuberia::colisionaCon(Tuberia *otraTuberia) {
    //todo: migrar a rectangulo_t
    unsigned short posXotraTuberia = otraTuberia->obtenerPosicionX();
    SDL_Rect dimensionesOtraTuberia = otraTuberia->obtenerDimensiones();
    dimensionesOtraTuberia.x += posXotraTuberia;
    dimensionesOtraTuberia.w += posXotraTuberia;
    return SDL_HasIntersection(&dimensiones, &dimensionesOtraTuberia);
}

unsigned short Tuberia::obtenerPosicionX() const {
    return posicion.obtenerPosX();
}

SDL_Rect Tuberia::obtenerDimensiones() {
    return dimensiones;
}

tuberia_t Tuberia::serializar(){
    unsigned short x = posicion.obtenerPosX();
    unsigned short y = posicion.obtenerPosY();
    return {x, y, color, tipo};
}

void Tuberia::elevar(int y) {
    posicion = PosicionFija(posicion.obtenerPosX(), posicion.obtenerPosY() + y);
    dimensiones.y += y; //todo: Migrar a rectangulo_t
    for(auto& pieza: piezas){
        pieza->elevar(y);
    }
}

list<PiezaDeTuberia *> Tuberia::obtenerPiezas() {
    return piezas;
}
