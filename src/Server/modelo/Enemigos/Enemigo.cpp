#include "Enemigo.hpp"
#include "src/Server/modelo/Mario/Mario.hpp"

int Enemigo::obtenerPosicionX() {
    return posicionActual->obtenerPosX();
}

int Enemigo::obtenerPosicionY() {
    return posicionActual->obtenerPosY();
}

void Enemigo::agregarPosicion(int coordenadaX, int coordenadaY) {
    posicionActual = new PosicionMovil(coordenadaX,coordenadaY);
}

void Enemigo::actualizarPosicion() {
    posicionActual->moverHorizontal(velocidadX);
    spriteEnemigo->actualizarSprite();
}

void Enemigo::morir() {
    spriteEnemigo->morir();
}

enemigo_t Enemigo::serializarEnemigo(int tipo) {
    enemigo_t enemigoSerializado;
    enemigoSerializado.posX = this->obtenerPosicionX();
    enemigoSerializado.numeroRecorteX = spriteEnemigo->obtenerEstadoActual();
    enemigoSerializado.numeroRecorteY = tipoColor;
    enemigoSerializado.tipoEnemigo = tipo;
    enemigoSerializado.espejar = velocidadX > 0;
    return enemigoSerializado;
}

bool Enemigo::sePuedeEliminar() {
    return spriteEnemigo->seMostroElTiempoSuficienteEnPantalla();
}

rectangulo_t Enemigo::obtenerRectangulo() {
    int x = this->obtenerPosicionX();
    int y = this->obtenerPosicionY();

    int h = 10; //todo obtener el valor
    int w = 20;
    rectangulo_t rectangulo = {x,x+w,y,y+h, w, h};
    return rectangulo;
}


