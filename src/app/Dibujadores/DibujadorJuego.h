#ifndef SRC_APP_DIBUJADORJUEGO_H_
#define SRC_APP_DIBUJADORJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#include "../../modelo/Juego.h"
#include "../../sprites/SpriteMario.h"
#include "Dibujador.h"

class DibujadorJuego : public Dibujador{

	public:
		DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);

		void dibujar(SDL_Rect* rectanguloCamara);
		void dibujar() override{
			// TODO: Esto está feo.
		}
		virtual ~DibujadorJuego(){}

	private:
		Uint32 tiempoDeInicio = 0;
		stringstream textoDeTiempo;
		stringstream textoDeNivel;
		stringstream textoDePuntos;

		SDL_Rect rectanguloCamara;
		Juego* juego;

		void dibujarEnemigos(SDL_Rect* rectanguloCamara);
		void dibujarPlataformas(SDL_Rect* rectanguloCamara);
		void dibujarMonedas(SDL_Rect* rectanguloCamara);
		void dibujarMario(SDL_Rect* rectanguloCamara);
		void dibujarTexto();

};

#endif /* SRC_APP_DIBUJADORJUEGO_H_ */
