#ifndef SRC_APP_DIBUJADORGANADORES_H_
#define SRC_APP_DIBUJADORGANADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Dibujador.hpp"
#include "ParticulaGanadores.hpp"

#include "../juegoCliente/JuegoCliente.hpp"

#include "../../../Server/sprites/spritesPersonajesSaltando/SpritePeachSaltando.hpp"
#include "../../../Server/sprites/spritesPersonajesSaltando/SpriteToadSaltando.hpp"
#include "../../../Server/sprites/spritesPersonajesSaltando/SpriteYoshiSaltando.hpp"


class DibujadorGanadores : public Dibujador{
	public:
		DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar(JuegoCliente* juegoCliente);
		~DibujadorGanadores();

	private:
		void dibujarTextoGanadores(JuegoCliente* juegoCliente);
		void dibujarParticulas();
		void dibujarPersonajes();

		map<int, SDL_Color> colores;
		SpritePeachSaltando* spritePeach;
		SpriteToadSaltando* spriteToad;
		SpriteYoshiSaltando* spriteYoshi;
		list<ParticulaGanadores*> particulas;
};


#endif /* SRC_APP_DIBUJADORGANADORES_H_ */
