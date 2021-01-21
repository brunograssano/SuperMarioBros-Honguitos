#include "DibujadorGanadores.hpp"
#include "src/Client/app/Dibujadores/Recortes/spritesPersonajesSaltando/RecortePeachSaltando.hpp"
#include "src/Client/app/Dibujadores/Recortes/spritesPersonajesSaltando/RecorteToadSaltando.hpp"
#include "src/Client/app/Dibujadores/Recortes/spritesPersonajesSaltando/RecorteYoshiSaltando.hpp"

#include "src/Client/app/ManejadorSDL.hpp" //todo: ver si se usa


DibujadorGanadores::DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador= renderizador;
	this->ancho_pantalla = ancho_pantalla;
	this->alto_pantalla = alto_pantalla;
	this->dibujadorPuntos = new DibujadorPuntos(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
    this->dibujadorCreditos = new DibujadorCreditos(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);

    this->botonIzquierdo = new BotonConTexto(ancho_pantalla/4 - 200/2 - 25 - 40 ,175,40,40, "<<", renderizador, cargarFuente("resources/Fuentes/fuenteSuperMarioBros.ttf", 12));
    this->botonDerecho = new BotonConTexto(ancho_pantalla/4 - 200/2- 25 + 250,175,40,40, ">>", renderizador, cargarFuente("resources/Fuentes/fuenteSuperMarioBros.ttf", 12));

    string listaParticulas[]={"resources/Imagenes/Particulas/confetiAzul.png","resources/Imagenes/Particulas/confetiAmarillo.png",
							  "resources/Imagenes/Particulas/confetiRosa.png","resources/Imagenes/Particulas/confetiVerde.png"};
	for(int i=0;i<700;i++){
		int posX = rand() % ancho_pantalla;
		int posY = rand() % alto_pantalla;
		float factorAvance = rand() % 3 + 1;
		particulas.push_front(ParticulaGanadores(posX,posY,listaParticulas[i%4],factorAvance));
	}

	spritePeach = new RecortePeachSaltando();
	spriteToad = new RecorteToadSaltando();
	spriteYoshi = new RecorteYoshiSaltando();

}

void DibujadorGanadores::dibujarTextoGanadores(JuegoCliente* juegoCliente) {
    botonIzquierdo->mostrarse();
    botonDerecho->mostrarse();
    int ultimoNivel = juegoCliente->obtenerNivelesJugados()-1;
    dibujarTitulo(juegoCliente->obtenerJugadores()[juegoCliente->obtenerPodioPuntosAcumulados().ids[0]].nombreJugador);

    if (botonIzquierdo->botonClickeado(this->eventoMouse)) {
        dibujadorPuntos->disminuirNivelAMostrarPuntos(ultimoNivel);
        this->eventoMouse.type = 0;
    } else if (botonDerecho->botonClickeado(this->eventoMouse)) {
        dibujadorPuntos->aumentarNivelAMostrarPuntos(ultimoNivel);
        this->eventoMouse.type = 0;
    }
    dibujadorPuntos->dibujarPuntos(juegoCliente);
    dibujadorCreditos->dibujarCreditos();
}

void DibujadorGanadores::dibujarTitulo(const string& nombreGanador){
    stringstream textoFelicitaciones;
    textoFelicitaciones.str("");
    textoFelicitaciones << "HAS GANADO: "<< nombreGanador;
    int ancho_textoFelicitaciones = 400;
    int alto_textoFelicitaciones = 60;

    SDL_Rect cuadradoFin = {ancho_pantalla/2 -ancho_textoFelicitaciones/2,
                            alto_pantalla/2 - alto_textoFelicitaciones/2 - 225,
                            ancho_textoFelicitaciones,
                            alto_textoFelicitaciones};
    renderizarTexto(cuadradoFin, textoFelicitaciones.str(), colorDefault);
}


void DibujadorGanadores::dibujarParticulas(){
	SDL_Rect* clip = nullptr;
	double angle = 0.0;
	SDL_Point* center = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	for(auto particula:particulas){
		SDL_Rect renderQuad = { particula.obtenerX(), particula.obtenerY(), 10, 10 };
		SDL_RenderCopyEx( renderizador, cargadorTexturas->obtenerParticula(particula.particulaAsociada()), clip, &renderQuad, angle, center, flip );
	}
}

void DibujadorGanadores::dibujarPersonajes(){
	SDL_Rect rectanguloPeach = {40, alto_pantalla - (int)(alto_pantalla*0.1)-80, 52, 80};
	SDL_Rect rectanguloToad = {200, alto_pantalla - (int)(alto_pantalla*0.1)-83 , 52, 80};
	SDL_Rect rectanguloYoshi = {400, alto_pantalla - (int)(alto_pantalla*0.1)-83, 52, 80};
	SDL_Rect recortePeach = spritePeach->obtenerRecorte(0);
	SDL_Rect recorteToad = spriteToad->obtenerRecorte(0);
	SDL_Rect recorteYoshi = spriteYoshi->obtenerRecorte(0);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_PEACH_SALTANDO), &recortePeach , &rectanguloPeach);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_TOAD_SALTANDO), &recorteToad , &rectanguloToad);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura(CLAVE_TEXTURA_YOSHI_SALTANDO), &recorteYoshi , &rectanguloYoshi);

}


void DibujadorGanadores::dibujar(JuegoCliente* juegoCliente){
	SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 255 );
	SDL_RenderClear( renderizador );
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTextura("FondoGanadores"), nullptr, nullptr);

	dibujarParticulas();
	dibujarTextoGanadores(juegoCliente);
	dibujarPersonajes();
	SDL_RenderPresent( renderizador );
	for(auto& particula:particulas){
		particula.actualizarPosicion(alto_pantalla);
	}
	spritePeach->actualizarSprite();
	spriteToad->actualizarSprite();
	spriteYoshi->actualizarSprite();
}

DibujadorGanadores::~DibujadorGanadores(){
	particulas.clear();
	delete this->dibujadorPuntos;
	delete this->dibujadorCreditos;
	delete this->botonDerecho;
	delete this->botonIzquierdo;
}

void DibujadorGanadores::agregarEventoDeClick(SDL_Event eventoClick) {
    this->eventoMouse = eventoClick;
}
