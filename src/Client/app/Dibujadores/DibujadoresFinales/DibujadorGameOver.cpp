#include "DibujadorGameOver.hpp"


DibujadorGameOver::DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->spriteCoffinMario = RecorteCoffinMario();
    this->botonIzquierdo = new BotonConTexto(ancho_pantalla/4 - 200/2 - 25 - 40 ,175,40,40, "<<", renderizador, cargarFuente("resources/Fuentes/fuenteSuperMarioBros.ttf", 12));
    this->botonDerecho = new BotonConTexto(ancho_pantalla/4 - 200/2- 25 + 250,175,40,40, ">>", renderizador, cargarFuente("resources/Fuentes/fuenteSuperMarioBros.ttf", 12));
	this->dibujadorPuntos = new DibujadorPuntos(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
    this->dibujadorCreditos = new DibujadorCreditos(cargadorTexturas,renderizador,ancho_pantalla,alto_pantalla);
}


void DibujadorGameOver::dibujar(JuegoCliente* juegoCliente){

	SDL_RenderClear( renderizador );

	SDL_Rect rectanguloCamara = {0, 0, alto_pantalla, ancho_pantalla};
	this->spriteCoffinMario.actualizarSprite();
	int posicionXCoffinMario = this->spriteCoffinMario.obtenerPosicionX();
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_GAMEOVER), &rectanguloCamara, nullptr);

    int piso = 440;
    SDL_Rect rectanguloCoffinMario = {posicionXCoffinMario, piso, 3*70, 3*32};
    SDL_Rect recorteCoffinMario = this->spriteCoffinMario.obtenerRecorte(0);
    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_COFFIN_MARIO), &recorteCoffinMario , &rectanguloCoffinMario);


    this->dibujadorCreditos-> dibujarCreditos();
	/* todo MODULARIZAR*/
    botonIzquierdo->mostrarse();
    botonDerecho->mostrarse();
    int ultimoNivel = juegoCliente->obtenerNivelesJugados()-1;

    if (botonIzquierdo->botonClickeado(this->eventoMouse)) {
        dibujadorPuntos->disminuirNivelAMostrarPuntos(ultimoNivel);
        this->eventoMouse.type = NULL;
    } else if (botonDerecho->botonClickeado(this->eventoMouse)) {
        dibujadorPuntos->aumentarNivelAMostrarPuntos(ultimoNivel);
        this->eventoMouse.type = NULL;
    }
    dibujadorPuntos->dibujarPuntosGameOver(juegoCliente);
	/**/

	stringstream textoGameOver;
	textoGameOver.str("");
	textoGameOver << "GAME OVER";
	int ancho_textoGameOver = 450;
	int alto_textoGameOver = 80;
	SDL_Rect cuadradoGameOver = {ancho_pantalla/2 -ancho_textoGameOver/2,
							alto_pantalla/7 - 40,
							ancho_textoGameOver,
							alto_textoGameOver}; //Los coloco en el centro.

	renderizarTexto(cuadradoGameOver, textoGameOver.str(), colorDefault);

	SDL_RenderPresent(renderizador);
}

DibujadorGameOver::~DibujadorGameOver(){
	delete this->dibujadorPuntos;
	delete this->dibujadorCreditos;
	delete this->botonIzquierdo;
	delete this->botonDerecho;
}

void DibujadorGameOver::agregarEventoDeClick(SDL_Event eventoClick) {
    this->eventoMouse = eventoClick;
}
