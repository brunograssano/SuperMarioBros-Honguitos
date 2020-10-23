#include "Dibujador.h"
#include "App.h"


Dibujador::Dibujador(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador,SpriteMario* spriteMario){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->juego = Juego::getInstance();
	this->spriteMario = spriteMario;
}


void Dibujador::dibujarGameOver(){
	SDL_RenderClear( renderizador );

	// TODO QUE ALGUIEN SE FIJE BIEN COMO PONER UN FONDO NEGRO Y EN BLANCO ARRIBA GAME OVER

	//SDL_Rect fillRect = { 0, 0, 800, 600};
	//SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 0xFF );
	//SDL_RenderFillRect( renderizador, &fillRect );
	//SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	//SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
	//SDL_RenderDrawRect( renderizador, &fillRect );


	stringstream textoGameOver;
	textoGameOver.str("");
	textoGameOver << "GAME OVER";
	SDL_Rect cuadradoGameOver = { 200, 300, 330, 0 };
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_SetRenderDrawColor( renderizador, 220, 220, 220, 0 );
	SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoGameOver.str(), renderizador);
	SDL_RenderCopyEx( renderizador, texto, clip, &cuadradoGameOver, angle, center, flip );
	SDL_DestroyTexture(texto);

	SDL_RenderPresent( renderizador );
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

		SDL_Rect rectanguloEnemigo = {enemigo->obtenerPosicionX()-rectanguloCamara->x, 472 , 32, 64};

	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(spriteEnemigo,renderizador), &recorteTextura, &rectanguloEnemigo);
	}
}

void Dibujador::dibujarPlataformas(SDL_Rect* rectanguloCamara){
	list<Plataforma*> plataformas = Juego::getInstance()->obtenerPlataformas();

	for(auto const& plataforma : plataformas){
		list<Bloque*> bloques = plataforma->obtenerBloques();
		for (auto const& bloque : bloques) {

			SDL_Rect rectanguloBloque = {bloque->obtenerPosicionX() - rectanguloCamara->x,bloque->obtenerPosicionY(), 40, 40};
			Sprite* spriteBloque = bloque->obtenerSprite();
			SDL_Rect recorteBloque = spriteBloque->obtenerRectanguloActual();
			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaBloque(spriteBloque, renderizador), &recorteBloque, &rectanguloBloque);
		}
	}
}

void Dibujador::dibujarMonedas(SDL_Rect* rectanguloCamara){
	list<Moneda*> monedas = Juego::getInstance()->obtenerMonedas();
	for (auto const& moneda : monedas) {
		SDL_Rect rectanguloMoneda = {moneda->obtenerPosicionX() - rectanguloCamara->x,moneda->obtenerPosicionY(), 40, 40};
		Sprite* spriteMoneda = moneda->obtenerSprite();
		spriteMoneda->actualizarSprite();
		SDL_Rect recorteMoneda = spriteMoneda->obtenerRectanguloActual();
		SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMoneda(), &recorteMoneda, &rectanguloMoneda);

	}
}

void Dibujador::dibujarMario(SDL_Rect* rectanguloCamara){
	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX() - rectanguloCamara->x,458 - mario->obtenerPosicionY(), 40, 80};
	int recorteX = spriteMario->obtenerPosicionXRectangulo();
	SDL_Rect recorteMario = {recorteX, 0, 16, 32};
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), &recorteMario, &rectanguloMario);
}

void Dibujador::dibujarTexto(){
	textoDeTiempo.str( "" );
	int tiempo = App::getInstance()->obtenerTiempoFaltante();//((juego->obtenerTiempoDelNivel()*1000) - SDL_GetTicks() - tiempoDeInicio)/1000; //Getticks devuelve en milisegundos
	textoDeTiempo << "Tiempo restante " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juego->obtenerMundoActual();

	textoDePuntos.str("");
	textoDePuntos << "Puntos " << juego->obtenerPuntuacionJugador();
	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Rect cuadradoTiempo = { 450, 10, 330, 30 };
	SDL_Rect cuadradoMundo = { 200, 10, 100, 30 };
	SDL_Rect cuadradoPuntos = { 10, 10, 100, 30 };

	renderizarTexto(cuadradoTiempo, textoDeTiempo.str().c_str());
	renderizarTexto(cuadradoMundo, textoDeNivel.str().c_str());
	renderizarTexto(cuadradoPuntos, textoDePuntos.str().c_str());
}

void Dibujador::renderizarTexto(SDL_Rect renderQuad,string textoAMostrar ){
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador);

	SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
	SDL_DestroyTexture(texto);
}
