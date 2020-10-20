
#ifndef SRC_SPRITES_SPRITEMONEDA_H_
#define SRC_SPRITES_SPRITEMONEDA_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteGoomba : public Sprite{
	public:

		SpriteGoomba(string direccionImagen);
		~SpriteGoomba(){};

		SDL_Rect obtenerRectanguloActual()override;

		int obtenerPosicionXRectangulo()override;

		void actualizarSprite()override;

	private:

		bool cambio;
		int ciclos;
		int estadoActual;
		SDL_Rect estadosPosibles[3];
		int ancho;
		int alto;
};


#endif /* SRC_SPRITES_SPRITEMONEDA_H_ */
