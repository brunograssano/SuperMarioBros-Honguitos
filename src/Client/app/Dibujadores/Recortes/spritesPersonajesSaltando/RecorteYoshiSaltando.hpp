#ifndef SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_
#define SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_

#include "src/Client/app/Dibujadores/Recortes/Recorte.hpp"

class RecorteYoshiSaltando: public Recorte{

	public:
		RecorteYoshiSaltando();
		void actualizarSprite()override;
        SDL_Rect obtenerRecorte(int recorte)override;

	private:
		int estadoActual;
        int ciclos{};

};




#endif /* SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_ */
