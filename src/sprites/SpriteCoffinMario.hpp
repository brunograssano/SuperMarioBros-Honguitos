#ifndef SRC_SPRITES_SPRITECOFFINMARIO_HPP_
#define SRC_SPRITES_SPRITECOFFINMARIO_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../app/CargadorTexturas.hpp"
#include "../modelo/Juego.hpp"
#include "Sprite.hpp"

class SpriteCoffinMario : public Sprite{

	public:

		SpriteCoffinMario();

		SDL_Rect obtenerRectanguloActual()override;

		int obtenerPosicionX();

		void actualizarSprite();

	private:
		SDL_Rect estadosPosibles[3];
		int estadoActual;
		int ciclos;
		int posicionX;
};


#endif /* SRC_SPRITES_SPRITECOFFINMARIO_HPP_ */
