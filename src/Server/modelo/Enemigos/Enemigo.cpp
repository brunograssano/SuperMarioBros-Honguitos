#include "Enemigo.hpp"
#include "src/Server/modelo/Mario/Mario.hpp"

int Enemigo::obtenerPosicionX() {
    return posicionActual->obtenerPosX();
}

int Enemigo::obtenerPosicionY() {
    return posicionActual->obtenerPosY();
}

void Enemigo::agregarPosicion(int coordenadaX, int coordenadaY) {
    delete posicionActual;
    posicionActual = new PosicionMovil(coordenadaX, coordenadaY);
}

void Enemigo::actualizarPosicion() {
    posicionActual->moverHorizontal(velocidadX);
    spriteEnemigo->actualizarSprite();
}

void Enemigo::morir(void* ptr) {
    loMataron = true;
    spriteEnemigo->morir();
    this->velocidadX = 0;
}


void Enemigo::cambiarOrientacion(void *ptr) {
    velocidadX = -velocidadX;
}

enemigo_t Enemigo::serializarEnemigo(int tipo) {
    enemigo_t enemigoSerializado;
    enemigoSerializado.posX = this->obtenerPosicionX();
    enemigoSerializado.posY = this->obtenerPosicionY();
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

    int h = ALTO_ENEMIGOS;
    int w = ANCHO_ENEMIGOS;
    rectangulo_t rectangulo = { x,x+w, y,y+h, h, w};
    return rectangulo;
}

bool Enemigo::estaMuerto() const{
    return loMataron;
}

void Enemigo::inicializarMapasDeColision() {
    auto pMorir = (void (Colisionable::*)(void*))&Enemigo::morir;
    auto pCambiarVelocidad = (void (Colisionable::*)(void*))&Enemigo::cambiarOrientacion;
    Colisionable::parFuncionColisionContexto_t parFuncionColisionContexto = {pMorir, nullptr};
    Colisionable::parFuncionColisionContexto_t parFuncionColisioBloque = {pCambiarVelocidad, nullptr};
    mapaColisionesPorArriba[COLISION_ID_MARIO] = parFuncionColisionContexto;
    mapaColisionesPorDerecha[COLISION_ID_LADRILLO] = parFuncionColisioBloque;
    mapaColisionesPorDerecha[COLISION_ID_SORPRESA] = parFuncionColisioBloque;
    mapaColisionesPorIzquierda[COLISION_ID_LADRILLO] = parFuncionColisioBloque;
    mapaColisionesPorIzquierda[COLISION_ID_SORPRESA] = parFuncionColisioBloque;
}

float Enemigo::obtenerVelocidad() {
    return (0.15 + ((rand() % 11) / 100)) * pow(-1,rand()%2);
}



