#include "DibujadorErrorServidor.hpp"

DibujadorErrorServidor::DibujadorErrorServidor(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla) {
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
}

void DibujadorErrorServidor::dibujar(){
	SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 255 );
	SDL_RenderClear( renderizador );

	stringstream textoError;
	textoError.str("");
	textoError << "Ocurrio un error en la conexion con el Servidor.";
	stringstream textoInfo;
	textoInfo.str("");
	textoInfo << "Para mas informacion revise su archivo log en la carpeta \"/logs/\"";

	int ancho_texto= 800;
	int alto_texto = 40;
	SDL_Rect rectanguloTextoError= {20,
							alto_pantalla/2 - alto_texto/2,
							ancho_texto,
							alto_texto};

	SDL_Rect rectanguloTextoInfo= {20,
							alto_pantalla/2 - alto_texto/2 + 100,
							ancho_texto-100,
							alto_texto};

	renderizarTexto(rectanguloTextoError, textoError.str().c_str(), colorDefault);
	renderizarTexto(rectanguloTextoInfo, textoInfo.str().c_str(), colorDefault);

	SDL_RenderPresent( renderizador );
}

DibujadorErrorServidor::~DibujadorErrorServidor(){}
