
#include <SDL2/SDL.h>

#include "SpriteEnemigo.hpp"

class SpriteGoomba : public SpriteEnemigo{
	public:

		explicit SpriteGoomba(int tipo);
		~SpriteGoomba() override= default;
		SDL_Rect obtenerRectanguloActual()override;
        void morir() override;
		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[3]{};

};
