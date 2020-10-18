
#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteGoomba : public Sprite{
	public:

		SpriteGoomba(string direccionImagen);
		~SpriteGoomba(){};

		SDL_Rect obtenerRectanguloActual()override;

	private:

		int estadoActual;
		SDL_Rect estadosPosibles[3];
		int ancho;
		int alto;
};
