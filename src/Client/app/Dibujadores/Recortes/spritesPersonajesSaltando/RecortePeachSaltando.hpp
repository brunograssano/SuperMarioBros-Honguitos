#ifndef SRC_SPRITES_SPRITEPEACH_HPP_
#define SRC_SPRITES_SPRITEPEACH_HPP_

#include "src/Client/app/Dibujadores/Recortes/Recorte.hpp"

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
