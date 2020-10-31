#ifndef SRC_APP_DIBUJADORGANADORES_H_
#define SRC_APP_DIBUJADORGANADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>


#include "Dibujador.hpp"
#include "../../sprites/spritesPersonajesSaltando/SpritePeachSaltando.hpp"
#include "../../sprites/spritesPersonajesSaltando/SpriteToadSaltando.hpp"
#include "../../sprites/spritesPersonajesSaltando/SpriteYoshiSaltando.hpp"

#include "../../modelo/Juego.hpp"
#include "ParticulaGanadores.hpp"

class DibujadorGanadores : public Dibujador{
	public:
		DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar() override;
		~DibujadorGanadores();

	private:
		void dibujarTextoGanadores();
		void dibujarParticulas();
		void dibujarPersonajes();

		SpritePeachSaltando* spritePeach;
		SpriteToadSaltando* spriteToad;
		SpriteYoshiSaltando* spriteYoshi;
		list<ParticulaGanadores*> particulas;
};


#endif /* SRC_APP_DIBUJADORGANADORES_H_ */
