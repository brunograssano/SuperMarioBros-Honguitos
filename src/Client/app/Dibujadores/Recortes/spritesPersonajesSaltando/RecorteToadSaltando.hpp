#ifndef SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_
#define SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_

#include "src/Client/app/Dibujadores/Recortes/Recorte.hpp"

class RecorteToadSaltando: public Recorte{

	public:
		RecorteToadSaltando();
		void actualizarSprite()override;
        int obtenerAltura() override;
        int obtenerAnchura() override;
		SDL_Rect obtenerRecorte(int recorte)override;

	private:
		SDL_Rect estadosPosibles[12]{};
		int estadoActual;
        int ciclos;

};



#endif /* SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_ */
