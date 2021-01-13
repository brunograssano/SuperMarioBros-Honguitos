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
		SDL_Rect obtenerRecorte(int recorte)override;
		int obtenerPosicionX() const;
		void actualizarSprite() override;
        int obtenerAltura() override;
        int obtenerAnchura() override;

	private:
        SDL_Rect estadosPosibles[3]{};
        int ciclos;
        int estadoActual;
		int posicionX;
};


#endif /* SRC_SERVER_SPRITES_SPRITECOFFINMARIO_HPP_ */
