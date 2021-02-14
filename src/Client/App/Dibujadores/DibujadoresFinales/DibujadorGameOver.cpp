#include "DibujadorGameOver.hpp"


DibujadorGameOver::DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla,JuegoCliente* juegoCliente){
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->juegoCliente = juegoCliente;
	this->spriteCoffinMario = RecorteCoffinMario();
	this->dibujadorPuntos = new DibujadorPuntos(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla, juegoCliente);
    this->dibujadorCreditos = new DibujadorCreditos(cargadorTexturas,renderizador,ancho_pantalla,alto_pantalla);
}


void DibujadorGameOver::dibujar(){
	SDL_RenderClear( renderizador );
    dibujarCoffinMario();
    dibujadorCreditos-> dibujar();
    dibujarPuntosObtenidosEnNiveles();
    dibujarTextoGameOver();
    SDL_RenderPresent(renderizador);
}

void DibujadorGameOver::dibujarCoffinMario() {
    SDL_Rect rectanguloCamara = {0, 0, alto_pantalla, ancho_pantalla};
    spriteCoffinMario.actualizarSprite();
    int posicionXCoffinMario = spriteCoffinMario.obtenerPosicionX();
    SDL_RenderCopy(renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_GAMEOVER), &rectanguloCamara, nullptr);

    int piso = 440;
    SDL_Rect rectanguloCoffinMario = {posicionXCoffinMario, piso, 3*70, 3*32};
    SDL_Rect recorteCoffinMario = spriteCoffinMario.obtenerRecorte(0);
    SDL_RenderCopy(renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_COFFIN_MARIO), &recorteCoffinMario , &rectanguloCoffinMario);
}

void DibujadorGameOver::dibujarPuntosObtenidosEnNiveles() {
    dibujadorPuntos->dibujar();
}

void DibujadorGameOver::dibujarTextoGameOver() {
    std::stringstream textoGameOver;
    textoGameOver.str("");
    textoGameOver << "GAME OVER";
    int ancho_textoGameOver = 450;
    int alto_textoGameOver = 80;
    SDL_Rect cuadradoGameOver = {ancho_pantalla / 2 - ancho_textoGameOver / 2,
                                 alto_pantalla / 7 - 40,
                                 ancho_textoGameOver, alto_textoGameOver}; //Los coloco en el centro.

    renderizarTexto(cuadradoGameOver, textoGameOver.str(), colorDefault);
}

void DibujadorGameOver::agregarEventoDeClick(SDL_Event eventoClick) {
    this->dibujadorPuntos->agregarEventoDeClick(eventoClick);
}

DibujadorGameOver::~DibujadorGameOver(){
    delete this->dibujadorPuntos;
    delete this->dibujadorCreditos;
}