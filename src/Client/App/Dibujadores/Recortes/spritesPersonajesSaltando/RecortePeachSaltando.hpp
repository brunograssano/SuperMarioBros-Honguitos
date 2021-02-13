#ifndef SRC_SPRITES_SPRITEPEACH_HPP_
#define SRC_SPRITES_SPRITEPEACH_HPP_

#include "../Recorte.hpp"
#include <SDL2/SDL.h>
class RecortePeachSaltando: public Recorte{

	public:
		RecortePeachSaltando();
		void actualizarSprite()override;
        SDL_Rect obtenerRecorte(int recorte)override;

	private:
		int estadoActual;
		int ciclos;

};



#endif /* SRC_SPRITES_SPRITEPEACH_HPP_ */
