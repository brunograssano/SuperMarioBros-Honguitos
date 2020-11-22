#include "DibujadorInicio.hpp"

#define DESFASE 20

DibujadorInicio::DibujadorInicio(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador= renderizador;
	this->ancho_pantalla = ancho_pantalla;
	this->alto_pantalla = alto_pantalla;
	SDL_QueryTexture(cargadorTexturas->obtenerTexturaFondoInicio(), (unsigned int*)NULL, (int*)NULL, &(this->ancho_fondo), &(this->alto_fondo));
	this->posicion_x_fondo = 0;
	this->ticks_salto_imagen = 0;
	this->ticks_salto_triangulo = 0;
	this->desfase = DESFASE;
}


void crearIndicacion(int* ticks, stringstream* indicacion){
	if(*ticks < 25){
		*indicacion << "> Jugar";
	}else if(*ticks < 50){
		*indicacion << "  Jugar";
	}else{
		*ticks= 0;
		*indicacion << "  Jugar";
	}
}

void DibujadorInicio::dibujar(){
	SDL_SetRenderDrawColor( renderizador, 120, 120, 200, 255 );
	SDL_RenderClear( renderizador );

	posicion_x_fondo += 1;
	if(posicion_x_fondo >= ancho_fondo - ancho_pantalla){
		posicion_x_fondo = 0;		//OJO: Esta transición "fluida" sólo sucede si la pantalla tiene las dimensiones mínimas (800 de ancho).
	}
	SDL_Rect rectanguloCamara = {(int)posicion_x_fondo, 0, alto_pantalla, ancho_pantalla};
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondoInicio(), &rectanguloCamara, NULL);

	ticks_salto_imagen++;
	if(ticks_salto_imagen >= 50){
		ticks_salto_imagen = 0;
		desfase *= -1;				// Se cambia la direccion del desfase
	}
	int ancho_titulo;
	int alto_titulo;
	SDL_QueryTexture(cargadorTexturas->obtenerTexturaTitulo(), (unsigned int*)NULL, (int*)NULL, &(ancho_titulo), &(alto_titulo));
	ancho_titulo /= 1.5;
	alto_titulo /= 1.5;
	SDL_Rect rectanguloTitulo = {ancho_pantalla/2 - ancho_titulo/2,
								alto_pantalla/2 - alto_titulo + desfase,
								ancho_titulo,
								alto_titulo};
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaTitulo(),NULL, &rectanguloTitulo);

	stringstream indicacion;
	indicacion.str("");
	ticks_salto_triangulo++;
	crearIndicacion(&ticks_salto_triangulo, &indicacion);
	int ancho_indicacion = 140;
	int alto_indicacion = 40;
	int desfase_alto_indicacion = 80;
	int desfase_ancho_indicacion = 15;
	SDL_Rect cuadradoIndicacion = {ancho_pantalla/2 -ancho_indicacion/2 - desfase_ancho_indicacion,
								alto_pantalla/2 - alto_indicacion/2 + desfase_alto_indicacion,
								ancho_indicacion,
								alto_indicacion};

	//renderizarTexto(cuadradoGameOver, titulo.str().c_str());
	renderizarTexto(cuadradoIndicacion, indicacion.str().c_str());
	SDL_RenderPresent(renderizador);

}


DibujadorInicio::~DibujadorInicio(){

}
