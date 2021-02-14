#ifndef SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_
#define SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_

#include "../Recorte.hpp"
#include <SDL2/SDL.h>
class RecorteToadSaltando: public Recorte{

	public:
		RecorteToadSaltando();
		void actualizarSprite()override;
        SDL_Rect obtenerRecorte(int recorte)override;

	private:
		int estadoActual;
        int ciclos{};

};



#endif /* SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_ */
