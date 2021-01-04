#ifndef SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_
#define SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Client/app/CargadorTexturas.hpp"
#include "../modelo/Juego.hpp"
#include "../sprites/Sprite.hpp"

class SpriteCoffinMario : public Sprite{

	public:

		SpriteCoffinMario();

		SDL_Rect obtenerRectanguloActual()override;

		int obtenerPosicionX() const;

		void actualizarSprite() override;

	private:
		SDL_Rect estadosPosibles[3]{};
		int posicionX;
};


#endif /* SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_ */
