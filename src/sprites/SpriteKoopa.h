/*
 * SpriteKoopa.h
 *
 *  Created on: 19 oct. 2020
 *      Author: adrianstarly
 */

#ifndef SRC_SPRITES_SPRITEKOOPA_H_
#define SRC_SPRITES_SPRITEKOOPA_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteKoopa : public Sprite{
	public:

		SpriteKoopa(string direccionImagen);
		~SpriteKoopa(){};

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

#endif /* SRC_SPRITES_SPRITEKOOPA_H_ */
