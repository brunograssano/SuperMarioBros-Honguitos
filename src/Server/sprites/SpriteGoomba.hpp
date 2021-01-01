
#include <SDL2/SDL.h>

#include "Sprite.hpp"

class SpriteGoomba : public Sprite{
	public:

		explicit SpriteGoomba(int tipo);
		~SpriteGoomba() override= default;;

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[3]{};

};
