#ifndef SRC_APP_DIBUJADORGAMEOVER_H_
#define SRC_APP_DIBUJADORGAMEOVER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#include <string>
#include <sstream>

#include "Dibujador.hpp"
#include "Recortes/RecorteCoffinMario.hpp"


class DibujadorGameOver : public Dibujador{

	public:
		DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar() override;
		~DibujadorGameOver() override;

	private:
		RecorteCoffinMario* spriteCoffinMario;
};



#endif /* SRC_APP_DIBUJADORGAMEOVER_H_ */
