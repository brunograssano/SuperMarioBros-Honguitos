#ifndef SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_
#define SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_

#include "../Recorte.hpp"
#include <SDL2/SDL.h>
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
