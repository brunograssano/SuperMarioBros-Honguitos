
#include <SDL2/SDL.h>
#include "Sprite.hpp"

class SpriteGoomba : public Sprite{
	public:

		SpriteGoomba(string direccionImagen);
		~SpriteGoomba(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:

		bool cambio;
		int ciclos;
		int estadoActual;
		SDL_Rect estadosPosibles[3];

};
