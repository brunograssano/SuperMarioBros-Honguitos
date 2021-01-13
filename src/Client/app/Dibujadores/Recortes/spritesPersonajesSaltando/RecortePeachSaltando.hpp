#ifndef SRC_SPRITES_SPRITEPEACH_HPP_
#define SRC_SPRITES_SPRITEPEACH_HPP_

#include "src/Client/app/Dibujadores/Recortes/Recorte.hpp"

class RecortePeachSaltando: public Recorte{

	public:
		RecortePeachSaltando();
		void actualizarSprite()override;
        int obtenerAltura() override;
        int obtenerAnchura() override;
		SDL_Rect obtenerRecorte(int recorte)override;

	private:
		SDL_Rect estadosPosibles[14]{};
		int estadoActual;
		int ciclos;

};



#endif /* SRC_SPRITES_SPRITEPEACH_HPP_ */
