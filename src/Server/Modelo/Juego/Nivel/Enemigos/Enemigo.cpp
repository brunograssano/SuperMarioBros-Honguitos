#include "Enemigo.hpp"
#include "src/Utils/Constantes.hpp"

#define MINIMO_COORDENADA_Y 0

int Enemigo::obtenerPosicionX() {
    return posicionActual.obtenerPosX();
}

int Enemigo::obtenerPosicionY() {
    return posicionActual.obtenerPosY();
}

void Enemigo::agregarPosicion(int coordenadaX, int coordenadaY) {
    posicionActual = PosicionMovil(coordenadaX, coordenadaY);
}

void Enemigo::actualizarPosicion(rectangulo_t rectangulo) {
    if(posicionActual.obtenerPosY() <= MINIMO_COORDENADA_Y){
        morir();
        return;
    }
    int posX = posicionActual.obtenerPosX();
    if(rectangulo.x1-ANCHO_ENEMIGOS*2<posX && posX<rectangulo.x2+ANCHO_ENEMIGOS*2){
        movimientoEnemigo.mover(&posicionActual);
        spriteEnemigo->actualizarSprite();
    }
    pisoBloque = false;
}

void Enemigo::morir(void* ptr) {
    loMataron = true;
    spriteEnemigo->morir();
    movimientoEnemigo.morir();
}


void Enemigo::cambiarOrientacion() {
    movimientoEnemigo.cambiarOrientacion();
    spriteEnemigo->espejar();
}

entidad_t Enemigo::serializarEnemigo(int tipo) {
    return Serializable::serializar(this->obtenerPosicionX(),this->obtenerPosicionY(),spriteEnemigo->obtenerEstadoActual(),tipoColor,tipo,spriteEnemigo->debeEspejarse());
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
    Colisionable::parFuncionColisionContexto_t morir = {pMorir, nullptr};

    mapaColisionesPorArriba[COLISION_ID_MARIO] = morir;
    mapaColisionesPorDerecha[COLISION_ID_BOLA_DE_FUEGO] = morir;
    mapaColisionesPorIzquierda[COLISION_ID_BOLA_DE_FUEGO] = morir;
    mapaColisionesPorArriba[COLISION_ID_BOLA_DE_FUEGO] = morir;
    mapaColisionesPorAbajo[COLISION_ID_BOLA_DE_FUEGO] = morir;
}

bool Enemigo::debeColisionar() {
    return !estaMuerto();
}


void Enemigo::chocarPorDerechaCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnX(colisionable->obtenerRectangulo(),IZQUIERDA);
    }
    else{
        Colisionable::chocarPorDerechaCon(colisionable);
    }
}

void Enemigo::chocarPorIzquierdaCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnX(colisionable->obtenerRectangulo(),DERECHA);
    }
    else{
        Colisionable::chocarPorIzquierdaCon(colisionable);
    }
}

void Enemigo::empujarEnX(rectangulo_t rectanguloBloque,int direccion){
    cambiarOrientacion();
    rectangulo_t rectanguloEnemigo = obtenerRectangulo();
    if(direccion == DERECHA){
        this->posicionActual.moverHorizontal(rectanguloBloque.x2-rectanguloEnemigo.x1);
    }
    else{
        this->posicionActual.moverHorizontal(-(rectanguloEnemigo.x2-rectanguloBloque.x1));
    }
}

void Enemigo::chocarPorAbajoCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnY(colisionable->obtenerRectangulo(),ARRIBA);
    }
    else{
        Colisionable::chocarPorAbajoCon(colisionable);
    }
}

void Enemigo::empujarEnY(rectangulo_t rectanguloBloque, int direccion) {
    movimientoEnemigo.setVelocidadY(0);
    rectangulo_t rectanguloEnemigo = obtenerRectangulo();
    if(direccion == ABAJO){
        this->posicionActual.moverVertical(-(rectanguloEnemigo.y2-rectanguloBloque.y1));
    }
    else{
        // El -1 es para que aún sigan colisionando contra el bloque en el que están parados
        // Sin este -1 estamos separando al enemigo lo suficiente del bloque como para que dependa
        // de cuan rapido caiga (su gravedad) switcheando aire y tierra constantemente.
        this->posicionActual.moverVertical(rectanguloBloque.y2 - rectanguloEnemigo.y1 - 1);
        pisoBloque = true;
    }
}