#include "Mario.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Server/sprites/SpriteMario.hpp"

const int COORDENADA_X_DEFAULT = 20,COORDENADA_Y_DEFAULT = 0;
const int MINIMO_COORDENADA_Y = 0;
const int TERRENO_LIMITE_DERECHO_MAX = 8177,TERRENO_LIMITE_DERECHO_MIN = 0;
const short MARIO_DESCONECTADO = -1;


Mario::Mario(int numeroJugador){
	this->posicion = new PosicionMovil(COORDENADA_X_DEFAULT,COORDENADA_Y_DEFAULT, MINIMO_COORDENADA_Y,
			TERRENO_LIMITE_DERECHO_MIN, TERRENO_LIMITE_DERECHO_MAX);
	this->puntos=0;
	this->movimiento = new MovimientoMario();
	this->spriteMario = new SpriteMario();
	this->modificador = new SinModificador();
	this->vidaMario = new VidaMario();
	this->numeroJugador = numeroJugador;
	this->estaConectadoElJugador = true;
    inicializarMapasDeColision();
}

void Mario::inicializarMapasDeColision(){
    auto pPerderVida = (void (Colisionable::*)(void*))&Mario::perderVida;
    auto pMatar = (void (Colisionable::*)(void*)) &Mario::matarEnemigo;
    auto pGanarPuntos = (void (Colisionable::*)(void*)) &Mario::agregarPuntos;

    Colisionable::parFuncionColisionContexto_t parPerderVida = {pPerderVida, nullptr};
    Colisionable::parFuncionColisionContexto_t parMatarGoomba = {pMatar, (void *) &PUNTOS_GOOMBA};
    Colisionable::parFuncionColisionContexto_t parMatarKoopa = {pMatar, (void *) &PUNTOS_KOOPA};
    Colisionable::parFuncionColisionContexto_t parAgarrarMoneda = {pGanarPuntos, (void* ) &PUNTOS_POR_MONEDA};

    mapaColisionesPorDerecha[COLISION_ID_KOOPA] = parPerderVida;
    mapaColisionesPorDerecha[COLISION_ID_GOOMBA] = parPerderVida;
    mapaColisionesPorDerecha[COLISION_ID_MONEDA] = parAgarrarMoneda;

    mapaColisionesPorIzquierda[COLISION_ID_KOOPA] = parPerderVida;
    mapaColisionesPorIzquierda[COLISION_ID_GOOMBA] = parPerderVida;
    mapaColisionesPorIzquierda[COLISION_ID_MONEDA] = parAgarrarMoneda;

    mapaColisionesPorArriba[COLISION_ID_KOOPA] = parPerderVida;
    mapaColisionesPorArriba[COLISION_ID_GOOMBA] = parPerderVida;
    mapaColisionesPorArriba[COLISION_ID_MONEDA] = parAgarrarMoneda;

    mapaColisionesPorAbajo[COLISION_ID_KOOPA] = parMatarKoopa;
    mapaColisionesPorAbajo[COLISION_ID_GOOMBA] = parMatarGoomba;
    mapaColisionesPorAbajo[COLISION_ID_MONEDA] = parAgarrarMoneda;

}

SpriteMario* Mario::obtenerSpite(){
	return spriteMario;
}

void Mario::actualizarSaltarMario(){
	movimiento->saltar();
	spriteMario->actualizarSpriteMarioSaltar();
}

void Mario::actualizarAgacharseMario(){
	spriteMario->actualizarSpriteMarioAgacharse();
}

void Mario::actualizarIzquierdaMario(){
	spriteMario->actualizarSpriteMarioIzquierda(this);
	movimiento->aceleraraIzquierda();
}

void Mario::actualizarDerechaMario(){
	spriteMario->actualizarSpriteMarioDerecha(this);
	movimiento->aceleraraDerecha();
}

void Mario::actualizarMaximoX(int limite){
    this->posicion->actualizarLimiteTerrenoIzq(limite);
}

void Mario::actualizarMinimoX(int limite){
    this->posicion->actualizarLimiteTerrenoDer(limite);
}

int Mario::obtenerPosicionX(){
	return posicion->obtenerPosX();
}

int Mario::obtenerPosicionY(){
	return posicion->obtenerPosY();
}

int Mario::obtenerPuntos() const{
	return puntos;
}

void Mario::agregarPuntos(int unosPuntos){
	puntos+=unosPuntos;
}

void Mario::agregarMoneda(){
    puntos+=PUNTOS_POR_MONEDA;
}

jugador_t Mario::serializar(const char nombreJugador[MAX_NOMBRE], unsigned short idImagen){
	jugador_t jugadorSerializado;
	strcpy(jugadorSerializado.nombreJugador, nombreJugador);
	jugadorSerializado.puntos = puntos;
	mario_t marioSerializado;
	marioSerializado.idImagen = idImagen;
	marioSerializado.posX = posicion->obtenerPosX();
	marioSerializado.posY = posicion->obtenerPosY();
	marioSerializado.recorteImagen = spriteMario->obtenerEstadoActual();
    marioSerializado.vidas = vidaMario->obtenerVida();
	if(!estaConectadoElJugador){
		marioSerializado.recorteImagen = MARIO_DESCONECTADO;
	}
	jugadorSerializado.mario = marioSerializado;
	return jugadorSerializado;
}


void Mario::reiniciarPosicion(){
	delete posicion;
	delete movimiento;
	movimiento = new MovimientoMario();
	posicion = new PosicionMovil(COORDENADA_X_DEFAULT,COORDENADA_Y_DEFAULT, MINIMO_COORDENADA_Y,
			TERRENO_LIMITE_DERECHO_MIN, TERRENO_LIMITE_DERECHO_MAX);
}


void Mario::actualizarPosicion(){
	this->movimiento->mover(this->posicion);
	if(this->posicion->obtenerPosY() == MINIMO_COORDENADA_Y){ //TODO Ojo cuando vayamos a trabajar con floats... y el "==". Cambiar por un intervalo.
		this->movimiento->setVelocidadY(0);
	}
	spriteMario->actualizarSprite(this);
	modificador->actualizar();
	Log::getInstance()->mostrarPosicion("Mario", posicion->obtenerPosX(), posicion->obtenerPosY());
}

bool Mario::estaConectado() const{
	return this->estaConectadoElJugador;
}

void Mario::serArrastrado(int corrimiento){
	this->posicion->moverHorizontal(corrimiento);
}

bool Mario::estaQuietoX(){
	return this->movimiento->estaQuieto();
}

bool Mario::estaEnElPiso(){
    return !movimiento->estaEnElAire();
}

void Mario::swapDeModificador(ModificadorMario* nuevoModificador){
    delete modificador;
    modificador = nuevoModificador;
}

int Mario::obtenerVida(){
    return vidaMario->obtenerVida();
}

void Mario::perderVida(void* ptr) {
    ModificadorMario* nuevoModificador = modificador->perderVida(vidaMario);
    posicion->reiniciar();
    movimiento->reiniciar();
    swapDeModificador(nuevoModificador);
}

void Mario::hacerseDeFuego() {
    ModificadorMario* nuevoModificador = modificador->hacerseDeFuego();
    swapDeModificador(nuevoModificador);
}

ObjetoFugaz* Mario::dispararFuego() {
    Posicion posManos = spriteMario->posicionManos();
    PosicionFija posicionManosMario(obtenerPosicionX() + posManos.obtenerPosX(),obtenerPosicionY() + posManos.obtenerPosY());
    return modificador->dispararFuego(posicionManosMario, spriteMario->direccionMirada(), movimiento->obtenerVelocidadXActual());
}

Mario::~Mario(){
	delete this->spriteMario;
	delete this->posicion;
	delete this->movimiento;
	delete this->modificador;
	delete this->vidaMario;
}

string Mario::obtenerColisionID() {
    return COLISION_ID_MARIO;
}

rectangulo_t Mario::obtenerRectangulo() {
    int x = this->obtenerPosicionX();
    int y = this->obtenerPosicionY();
    int h = ALTO_MARIO;
    int w = ANCHO_MARIO;
    rectangulo_t rectangulo = {x,x+w,y,y+h, h, w};
    return rectangulo;
}

void Mario::agregarPuntos(void *puntos) {
    if(puntos != nullptr){
        agregarPuntos(*((int*) puntos));
    }
}

void Mario::matarEnemigo(void* puntos){
    movimiento->impulsarY();
    if(puntos != nullptr) {
        agregarPuntos(*((int *) puntos));
    }
    spriteMario->actualizarSpriteMarioSaltar();
}

void Mario::chocarPorDerechaCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnX(colisionable->obtenerRectangulo(),IZQUIERDA);
    }
    else{
        Colisionable::chocarPorDerechaCon(colisionable);
    }
}

void Mario::chocarPorIzquierdaCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnX(colisionable->obtenerRectangulo(),DERECHA);
    }
    else{
        Colisionable::chocarPorIzquierdaCon(colisionable);
    }
}

void Mario::chocarPorArribaCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnY(colisionable->obtenerRectangulo(),ABAJO);
    }
    else {
        Colisionable::chocarPorArribaCon(colisionable);
    }
}

void Mario::chocarPorAbajoCon(Colisionable *colisionable) {
    if(esUnBloque(colisionable->obtenerColisionID())){
        empujarEnY(colisionable->obtenerRectangulo(),ARRIBA);
    }
    else{
        Colisionable::chocarPorAbajoCon(colisionable);
    }
}

void Mario::empujarEnX(rectangulo_t rectanguloBloque,int direccion){
    movimiento->setVelocidadX(0);
    rectangulo_t rectanguloMario = obtenerRectangulo();
    if(direccion == DERECHA){
        this->posicion->moverHorizontal(rectanguloBloque.x2-rectanguloMario.x1);
    }
    else{
        this->posicion->moverHorizontal(-(rectanguloMario.x2-rectanguloBloque.x1));
    }
}

void Mario::empujarEnY(rectangulo_t rectanguloBloque, int direccion) {
    movimiento->setVelocidadY(0);
    rectangulo_t rectanguloMario = obtenerRectangulo();
    if(direccion == ABAJO){
        this->posicion->moverVertical(-(rectanguloMario.y2-rectanguloBloque.y1));
    }
    else{
        this->posicion->moverVertical(rectanguloBloque.y2-rectanguloMario.y1);
        this->movimiento->teParasteEnBloque();
    }
}

bool Mario::debeColisionar() {
    return estaConectadoElJugador && vidaMario->obtenerVida() > 0;
}
