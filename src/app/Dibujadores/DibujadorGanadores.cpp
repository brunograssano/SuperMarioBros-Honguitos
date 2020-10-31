#include "DibujadorGanadores.hpp"

DibujadorGanadores::DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador= renderizador;
	this->ancho_pantalla = ancho_pantalla;
	this->alto_pantalla = alto_pantalla;

	string listaParticulas[]={"resources/Particulas/confetiAzul.png","resources/Particulas/confetiAmarillo.png",
							  "resources/Particulas/confetiRosa.png","resources/Particulas/confetiVerde.png"};
	for(int i=0;i<700;i++){
		int posX = rand() % ancho_pantalla;
		int posY = rand() % alto_pantalla;
		float factorAvance = rand() % 3 + 1;
		particulas.push_front(new ParticulaGanadores(posX,posY,listaParticulas[i%4],factorAvance));
	}

	spritePeach = new SpritePeachSaltando();
	spriteToad = new SpriteToadSaltando();
	spriteYoshi = new SpriteYoshiSaltando();
}


void DibujadorGanadores::dibujarTextoGanadores(){
	stringstream textoFelicitaciones;
	textoFelicitaciones.str("");
	textoFelicitaciones << "GANARON EL JUEGO!";
	int ancho_textoFelicitaciones = 400;
	int alto_textoFelicitaciones = 60;
	SDL_Rect cuadradoFin = {ancho_pantalla/2 -ancho_textoFelicitaciones/2,
							alto_pantalla/2 - alto_textoFelicitaciones/2,
							ancho_textoFelicitaciones,
							alto_textoFelicitaciones}; //Los coloco en el centro.

	Juego* juego = Juego::getInstance();
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
}


void DibujadorGanadores::dibujarParticulas(){
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	for(auto const& particula:particulas){
		SDL_Rect renderQuad = { particula->obtenerX(), particula->obtenerY(), 10, 10 };
		SDL_RenderCopyEx( renderizador, cargadorTexturas->obtenerParticula(particula->particulaAsociada()), clip, &renderQuad, angle, center, flip );
	}
}

void DibujadorGanadores::dibujarPersonajes(){
	SDL_Rect rectanguloPeach = {40, alto_pantalla - (int)(alto_pantalla*0.1)-80, 52, 80};
	SDL_Rect rectanguloToad = {200, alto_pantalla - (int)(alto_pantalla*0.1)-83 , 52, 80};
	SDL_Rect rectanguloYoshi = {400, alto_pantalla - (int)(alto_pantalla*0.1)-83, 52, 80};
	SDL_Rect recortePeach = spritePeach->obtenerRectanguloActual();
	SDL_Rect recorteToad = spriteToad->obtenerRectanguloActual();
	SDL_Rect recorteYoshi = spriteYoshi->obtenerRectanguloActual();
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaPersonaje(spritePeach->direccionImagen()), &recortePeach , &rectanguloPeach);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaPersonaje(spriteToad->direccionImagen()), &recorteToad , &rectanguloToad);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaPersonaje(spriteYoshi->direccionImagen()), &recorteYoshi , &rectanguloYoshi);

}


void DibujadorGanadores::dibujar(){
	SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 255 );
	SDL_RenderClear( renderizador );
	SDL_Rect rectanguloCamara = {0, 0, alto_pantalla, ancho_pantalla};
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), &rectanguloCamara, NULL);
	dibujarParticulas();
	dibujarTextoGanadores();
	dibujarPersonajes();
	SDL_RenderPresent( renderizador );
	for(auto const& particula:particulas){
		particula->actualizarPosicion(alto_pantalla);
	}
	spritePeach->actualizarSprite();
	spriteToad->actualizarSprite();
	spriteYoshi->actualizarSprite();
}

DibujadorGanadores::~DibujadorGanadores(){
	for(auto const& particula:particulas){
		delete particula;
	}
	particulas.clear();
}
