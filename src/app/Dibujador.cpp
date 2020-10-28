#include "Dibujador.h"
#include "App.h"


const int ALTURA_SDL_PISO_MARIO = 458, ALTURA_SDL_PISO_ENEMIGOS = 472, ALTURA_SDL_PISO_BLOQUES = 800, ALTURA_SDL_PISO_MONEDAS = 600;
const float PROPORCION_PISO_EN_IMAGEN = 0.1;
const int ALTO_MARIO = 80, ANCHO_MARIO = 40;
const int ALTO_ENEMIGOS = 40, ANCHO_ENEMIGOS = 40;
const int LARGO_BLOQUE = 40;

Dibujador::Dibujador(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->juego = Juego::getInstance();
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->dibujadorGameOver = new DibujadorGameOver(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
}


void Dibujador::dibujarPantallaGanadores(){
	SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 255 );
	SDL_RenderClear( renderizador );

	stringstream textoFelicitaciones;
	textoFelicitaciones.str("");
	textoFelicitaciones << "GANARON EL JUEGO!";
	int ancho_textoFelicitaciones = 400;
	int alto_textoFelicitaciones = 60;
	SDL_Rect cuadradoFin = {ancho_pantalla/2 -ancho_textoFelicitaciones/2,
							alto_pantalla/2 - alto_textoFelicitaciones/2,
							ancho_textoFelicitaciones,
							alto_textoFelicitaciones}; //Los coloco en el centro.

	stringstream puntosJugador;
	puntosJugador.str("");
	puntosJugador << "Puntos obtenidos: " << juego->obtenerPuntuacionJugador();
	int ancho_puntosJugador = 500;
	int alto_puntosJugador = 40;
	int desfase_puntosJugador = 80;
	SDL_Rect cuadradoPuntos = {ancho_pantalla/2 -ancho_puntosJugador/2,
								alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador,
								ancho_puntosJugador,
								alto_puntosJugador};

	renderizarTexto(cuadradoFin, textoFelicitaciones.str().c_str());
	renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str());

	SDL_RenderPresent( renderizador );
}

void Dibujador::dibujarGameOver(){
	dibujadorGameOver->dibujar();
}

void Dibujador::dibujar(SDL_Rect* rectanguloCamara){

	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), rectanguloCamara, NULL);

	dibujarEnemigos(rectanguloCamara);
	dibujarPlataformas(rectanguloCamara);
	dibujarMonedas(rectanguloCamara);
	dibujarMario(rectanguloCamara);
	dibujarTexto();

	SDL_RenderPresent( renderizador );
}

void Dibujador::dibujarEnemigos(SDL_Rect* rectanguloCamara){
	list<Enemigo*> enemigos = Juego::getInstance()->obtenerEnemigos();
	for (auto const& enemigo : enemigos) {
		Sprite* spriteEnemigo = enemigo->obtenerSprite();
		SDL_Rect recorteTextura = spriteEnemigo->obtenerRectanguloActual();

		SDL_Rect rectanguloEnemigo = {enemigo->obtenerPosicionX()-rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - ALTO_ENEMIGOS,
									ANCHO_ENEMIGOS, ALTO_ENEMIGOS};

	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(spriteEnemigo,renderizador), &recorteTextura, &rectanguloEnemigo);
	}
}

void Dibujador::dibujarPlataformas(SDL_Rect* rectanguloCamara){
	list<Plataforma*> plataformas = Juego::getInstance()->obtenerPlataformas();

	for(auto const& plataforma : plataformas){
		list<Bloque*> bloques = plataforma->obtenerBloques();
		for (auto const& bloque : bloques) {

			SDL_Rect rectanguloBloque = {bloque->obtenerPosicionX() - rectanguloCamara->x,
										alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - bloque->obtenerPosicionY(),
										LARGO_BLOQUE, LARGO_BLOQUE};
			Sprite* spriteBloque = bloque->obtenerSprite();
			SDL_Rect recorteBloque = spriteBloque->obtenerRectanguloActual();
			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaBloque(spriteBloque, renderizador), &recorteBloque, &rectanguloBloque);
		}
	}
}

void Dibujador::dibujarMonedas(SDL_Rect* rectanguloCamara){
	list<Moneda*> monedas = Juego::getInstance()->obtenerMonedas();
	for (auto const& moneda : monedas) {
		SDL_Rect rectanguloMoneda = {moneda->obtenerPosicionX() - rectanguloCamara->x,
									alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) - moneda->obtenerPosicionY(),
									LARGO_BLOQUE, LARGO_BLOQUE};
		Sprite* spriteMoneda = moneda->obtenerSprite();
		spriteMoneda->actualizarSprite();
		SDL_Rect recorteMoneda = spriteMoneda->obtenerRectanguloActual();
		SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMoneda(), &recorteMoneda, &rectanguloMoneda);

	}
}

void Dibujador::dibujarMario(SDL_Rect* rectanguloCamara){
	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX() - rectanguloCamara->x,
								alto_pantalla - (int)(alto_pantalla*PROPORCION_PISO_EN_IMAGEN) -ALTO_MARIO- mario->obtenerPosicionY(),
								ANCHO_MARIO, ALTO_MARIO};
	SDL_Rect recorteMario = mario->obtenerSpite()->obtenerRectanguloActual();
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), &recorteMario, &rectanguloMario);
}

void Dibujador::dibujarTexto(){
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

void Dibujador::renderizarTexto(SDL_Rect renderQuad, string textoAMostrar ){
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador);

	SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
	SDL_DestroyTexture(texto);
}


Dibujador::~Dibujador(){
	delete dibujadorGameOver;
}
