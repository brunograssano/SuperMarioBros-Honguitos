#include "BolaDeFuego.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Server/modelo/Mario/Mario.hpp"

#define MAX_REBOTES 1

const float VELOCIDAD_X_INICIAL = 3.5;
const float VELOCIDAD_Y_INICIAL = 0;

BolaDeFuego::BolaDeFuego(const PosicionFija& posicionInicial, int direccion, float velocidadDeInercia, Mario* mario) {
    marioQueDisparo = mario;
    posicion = new PosicionMovil(posicionInicial.obtenerPosX(), posicionInicial.obtenerPosY());
    sprite = new SpriteBolaDeFuego();
    velocidadX = direccion==DERECHA?VELOCIDAD_X_INICIAL:-VELOCIDAD_X_INICIAL;
    velocidadX += velocidadDeInercia;
    velocidadY = VELOCIDAD_Y_INICIAL;
    exploto = false;
    manejadorSonido = ManejadorDeSonidoBolaDeFuego(mario->obtenerID());
    inicializarMapasDeColision();
}

bool BolaDeFuego::debeDesaparecer() {
    return sprite->terminoDeExplotar() || posicion->obtenerPosY() == 0;
}

void BolaDeFuego::actualizar() {
    posicion->moverHorizontal(velocidadX);
    posicion->moverVertical(velocidadY);
    sprite->actualizarSprite();
    velocidadY += efecto_gravitacional;
    if(posicion->obtenerPosY() <= 0 && rebotes < MAX_REBOTES){
        posicion->moverVertical(-posicion->obtenerPosY());
        rebotar(nullptr);
    }
}

BolaDeFuego::~BolaDeFuego() {
    delete posicion;
    delete sprite;
}

efecto_t BolaDeFuego::serializar() {
    auto posX = (unsigned short ) posicion->obtenerPosX();
    auto posY = (unsigned short ) posicion->obtenerPosY();
    return {posX, posY, static_cast<uint8_t>(sprite->obtenerEstadoActual()), BOLA_DE_FUEGO};
}

int BolaDeFuego::obtenerPosicionX() {
    return posicion->obtenerPosX();
}

string BolaDeFuego::obtenerColisionID() {
    return COLISION_ID_BOLA_DE_FUEGO;
}

rectangulo_t BolaDeFuego::obtenerRectangulo() {
    unsigned short x = posicion->obtenerPosX();
    unsigned short y = posicion->obtenerPosY();
    unsigned short w = ANCHO_BOLA;
    unsigned short h = ALTO_BOLA;
    return {x, x+w, y, y+h, h, w};
}

bool BolaDeFuego::debeColisionar() {
    return !exploto;
}

void BolaDeFuego::inicializarMapasDeColision() {
    auto pExplotar = (void (Colisionable::*)(void*))&BolaDeFuego::explotar;
    Colisionable::parFuncionColisionContexto_t parExplotar = {pExplotar, nullptr};

    auto pRebotar = (void (Colisionable::*)(void*))&BolaDeFuego::rebotar;
    Colisionable::parFuncionColisionContexto_t parRebotar = {pRebotar, nullptr};

    auto pMatarEnemigo = (void (Colisionable::*)(void*))&BolaDeFuego::matarEnemigo;
    Colisionable::parFuncionColisionContexto_t parMatarKoopa = {pMatarEnemigo, (void*) &PUNTOS_KOOPA};
    Colisionable::parFuncionColisionContexto_t parMatarGoomba = {pMatarEnemigo, (void*) &PUNTOS_GOOMBA};

    mapaColisionesPorDerecha[COLISION_ID_SORPRESA] = parExplotar;
    mapaColisionesPorIzquierda[COLISION_ID_SORPRESA] = parExplotar;
    mapaColisionesPorArriba[COLISION_ID_SORPRESA] = parExplotar;
    mapaColisionesPorAbajo[COLISION_ID_SORPRESA] = parRebotar;

    mapaColisionesPorDerecha[COLISION_ID_PIEZA_TUBERIA] = parExplotar;
    mapaColisionesPorIzquierda[COLISION_ID_PIEZA_TUBERIA] = parExplotar;
    mapaColisionesPorArriba[COLISION_ID_PIEZA_TUBERIA] = parExplotar;
    mapaColisionesPorAbajo[COLISION_ID_PIEZA_TUBERIA] = parRebotar;

    mapaColisionesPorDerecha[COLISION_ID_LADRILLO] = parExplotar;
    mapaColisionesPorIzquierda[COLISION_ID_LADRILLO] = parExplotar;
    mapaColisionesPorArriba[COLISION_ID_LADRILLO] = parExplotar;
    mapaColisionesPorAbajo[COLISION_ID_LADRILLO] = parRebotar;

    mapaColisionesPorDerecha[COLISION_ID_PLATAFORMA] = parExplotar;
    mapaColisionesPorIzquierda[COLISION_ID_PLATAFORMA] = parExplotar;
    mapaColisionesPorArriba[COLISION_ID_PLATAFORMA] = parExplotar;
    mapaColisionesPorAbajo[COLISION_ID_PLATAFORMA] = parRebotar;


    mapaColisionesPorDerecha[COLISION_ID_GOOMBA] = parMatarGoomba;
    mapaColisionesPorIzquierda[COLISION_ID_GOOMBA] = parMatarGoomba;
    mapaColisionesPorArriba[COLISION_ID_GOOMBA] = parMatarGoomba;
    mapaColisionesPorAbajo[COLISION_ID_GOOMBA] = parMatarGoomba;

    mapaColisionesPorDerecha[COLISION_ID_KOOPA] = parMatarKoopa;
    mapaColisionesPorIzquierda[COLISION_ID_KOOPA] = parMatarKoopa;
    mapaColisionesPorArriba[COLISION_ID_KOOPA] = parMatarKoopa;
    mapaColisionesPorAbajo[COLISION_ID_KOOPA] = parMatarKoopa;
}

void BolaDeFuego::chocarPorIzquierdaCon(Colisionable *colisionable) {
    manejadorSonido.reproducirSonidoIzquierda(colisionable->obtenerColisionID());
    Colisionable::chocarPorIzquierdaCon(colisionable);
}

void BolaDeFuego::chocarPorDerechaCon(Colisionable *colisionable) {
    manejadorSonido.reproducirSonidoDerecha(colisionable->obtenerColisionID());
    Colisionable::chocarPorDerechaCon(colisionable);
}

void BolaDeFuego::chocarPorArribaCon(Colisionable *colisionable) {
    manejadorSonido.reproducirSonidoArriba(colisionable->obtenerColisionID());
    Colisionable::chocarPorArribaCon(colisionable);
}


void BolaDeFuego::chocarPorAbajoCon(Colisionable *colisionable) {
    manejadorSonido.reproducirSonidoAbajo(colisionable->obtenerColisionID());
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarY(colisionable->obtenerRectangulo());
        rebotar(nullptr);
    }else{
        Colisionable::chocarPorAbajoCon(colisionable);
    }
}


void BolaDeFuego::explotar(void *pVoid) {
    velocidadY = 0;
    velocidadX = 0;
    efecto_gravitacional = 0;
    sprite->explotar();
    exploto = true;
}

void BolaDeFuego::rebotar(void *pVoid) {
    if(rebotes < MAX_REBOTES){
        velocidadY /= -1.3;
        velocidadY = velocidadY>3?3:velocidadY;
        rebotes++;
    }else{
        explotar(nullptr);
    }
}

void BolaDeFuego::matarEnemigo(void *pVoid) {
    int puntos = * ((int*) pVoid);
    marioQueDisparo->agregarPuntos(puntos);
    explotar(nullptr);
}

void BolaDeFuego::empujarY(rectangulo_t rectanguloEmpujador) {
    rectangulo_t rectanguloBola = obtenerRectangulo();
    int desplazamiento = rectanguloEmpujador.y2 - rectanguloBola.y1;
    this->posicion->moverVertical(desplazamiento);
}
