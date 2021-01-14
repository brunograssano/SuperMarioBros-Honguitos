#include "Mario.hpp"

const int COORDENADA_X_DEFAULT = 20,COORDENADA_Y_DEFAULT = 0;
const int MINIMO_COORDENADA_Y = 0;
const int TERRENO_LIMITE_DERECHO_MAX = 8177,TERRENO_LIMITE_DERECHO_MIN = 0;
const short MARIO_DESCONECTADO = -1;

const int PUNTOS_POR_MONEDA = 50;

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
	this->notificar();
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
	return this->posicion->obtenerPosY() == MINIMO_COORDENADA_Y;
}

void Mario::swapDeModificador(ModificadorMario* nuevoModificador){
    delete modificador;
    modificador = nuevoModificador;
}

int Mario::obtenerVida(){
    return vidaMario->obtenerVida();
}

void Mario::perderVida() {
    ModificadorMario* nuevoModificador = modificador->perderVida(vidaMario);
    swapDeModificador(nuevoModificador);
}

void Mario::hacerseDeFuego() {
    ModificadorMario* nuevoModificador = modificador->hacerseDeFuego();
    swapDeModificador(nuevoModificador);
}

Disparo* Mario::dispararFuego() {
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