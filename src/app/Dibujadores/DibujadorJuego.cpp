#include "DibujadorJuego.h"

#include "../App.h"
#include "Dibujadores.h"


const int ALTURA_SDL_PISO_MARIO = 458, ALTURA_SDL_PISO_ENEMIGOS = 472, ALTURA_SDL_PISO_BLOQUES = 800, ALTURA_SDL_PISO_MONEDAS = 600;
const float PROPORCION_PISO_EN_IMAGEN = 0.1;
const int ALTO_MARIO = 80, ANCHO_MARIO = 40;
const int ALTO_ENEMIGOS = 40, ANCHO_ENEMIGOS = 40;
const int LARGO_BLOQUE = 40;

DibujadorJuego::DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->juego = Juego::getInstance();
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
}

void DibujadorJuego::dibujar(SDL_Rect* rectanguloCamara){

	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), rectanguloCamara, NULL);

	dibujarEnemigos(rectanguloCamara);
	dibujarPlataformas(rectanguloCamara);
	dibujarMonedas(rectanguloCamara);
	dibujarMario(rectanguloCamara);
	dibujarTexto();

	SDL_RenderPresent( renderizador );
}

void DibujadorJuego::dibujarEnemigos(SDL_Rect* rectanguloCamara){
	list<Enemigo*> enemigos = Juego::getInstance()->obtenerEnemigos();
	for (auto const& enemigo : enemigos) {
		Sprite* spriteEnemigo = enemigo->obtenerSprite();
		SDL_Rect recorteTextura;
		recorteTextura = spriteEnemigo->obtenerRectanguloActual();

		SDL_Rect rectanguloEnemigo = {enemigo->obtenerPosicionX()-rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - ALTO_ENEMIGOS,
									ANCHO_ENEMIGOS, ALTO_ENEMIGOS};

	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(spriteEnemigo,renderizador), &recorteTextura, &rectanguloEnemigo);
	}
}

void DibujadorJuego::dibujarPlataformas(SDL_Rect* rectanguloCamara){
	list<Plataforma*> plataformas = Juego::getInstance()->obtenerPlataformas();

	for(auto const& plataforma : plataformas){
		list<Bloque*> bloques = plataforma->obtenerBloques();
		for (auto const& bloque : bloques) {

			SDL_Rect rectanguloBloque = {bloque->obtenerPosicionX() - rectanguloCamara->x,
										alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - bloque->obtenerPosicionY(),
										LARGO_BLOQUE, LARGO_BLOQUE};
			Sprite* spriteBloque = bloque->obtenerSprite();
			SDL_Rect recorteBloque;
			recorteBloque = spriteBloque->obtenerRectanguloActual();
			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaBloque(spriteBloque, renderizador), &recorteBloque, &rectanguloBloque);
		}
	}
}

void DibujadorJuego::dibujarMonedas(SDL_Rect* rectanguloCamara){
	list<Moneda*> monedas = Juego::getInstance()->obtenerMonedas();
	for (auto const& moneda : monedas) {
		SDL_Rect rectanguloMoneda = {moneda->obtenerPosicionX() - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - moneda->obtenerPosicionY(),
									LARGO_BLOQUE, LARGO_BLOQUE};
		Sprite* spriteMoneda = moneda->obtenerSprite();
		spriteMoneda->actualizarSprite();
		SDL_Rect recorteMoneda;
		recorteMoneda = spriteMoneda->obtenerRectanguloActual();
		SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMoneda(), &recorteMoneda, &rectanguloMoneda);

	}
}

void DibujadorJuego::dibujarMario(SDL_Rect* rectanguloCamara){
	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX() - rectanguloCamara->x,
								alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- mario->obtenerPosicionY(),
								ANCHO_MARIO, ALTO_MARIO};
	SDL_Rect recorteMario = mario->obtenerSpite()->obtenerRectanguloActual();
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), &recorteMario, &rectanguloMario);
}

void DibujadorJuego::dibujarTexto(){
	textoDeTiempo.str( "" );
	int tiempo = App::getInstance()->obtenerTiempoFaltante();
	textoDeTiempo << "Tiempo restante " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juego->obtenerMundoActual();

	textoDePuntos.str("");
	textoDePuntos << "Puntos " << juego->obtenerPuntuacionJugador();
	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Rect cuadradoTiempo = { ancho_pantalla - 340, 10, 330, 30 };
	SDL_Rect cuadradoMundo = { ancho_pantalla - ancho_pantalla/2 - 100, 10, 100, 30 };
	SDL_Rect cuadradoPuntos = { 10, 10, 100, 30 };

	renderizarTexto(cuadradoTiempo, textoDeTiempo.str().c_str());
	renderizarTexto(cuadradoMundo, textoDeNivel.str().c_str());
	renderizarTexto(cuadradoPuntos, textoDePuntos.str().c_str());
}
