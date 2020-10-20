
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

};
