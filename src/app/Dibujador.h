#ifndef SRC_APP_DIBUJADOR_H_
#define SRC_APP_DIBUJADOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#include "../modelo/Juego.h"
#include "CargadorTexturas.h"
#include "../sprites/SpriteMario.h"

#include "DibujadorGameOver.h"
#include "DibujadorInicio.h"
#include "DibujadorGanadores.h"
#include "DibujadorJuego.h"

class Dibujador{

	public:
		Dibujador(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, SpriteMario* spriteMario, int ancho_pantalla, int alto_pantalla);
		void dibujarJuego(SDL_Rect* rectanguloCamara);
		void dibujarGameOver();
		void dibujarInicio();
		void dibujarPantallaGanadores();
		~Dibujador();

	private:
		DibujadorGameOver* dibujadorGameOver;
		DibujadorInicio* dibujadorInicio;
		DibujadorGanadores* dibujadorGanadores;
		DibujadorJuego* dibujadorJuego;
};



#endif /* SRC_APP_DIBUJADOR_H_ */
