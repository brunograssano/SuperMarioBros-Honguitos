#ifndef SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_
#define SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "src/Client/app/CargadorTexturas.hpp"
#include "src/Server/modelo/Juego.hpp"
#include "Recorte.hpp"

class RecorteCoffinMario : public Recorte{

	public:

		RecorteCoffinMario();
		int obtenerPosicionX() const;
		void actualizarSprite() override;
        SDL_Rect obtenerRecorte(int recorte)override;

	private:
        int ciclos;
        int estadoActual;
		int posicionX;
};


#endif /* SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_ */
