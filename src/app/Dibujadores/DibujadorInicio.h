#ifndef SRC_APP_DIBUJADORINICIO_H_
#define SRC_APP_DIBUJADORINICIO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Dibujador.h"

class DibujadorInicio : public Dibujador{

	public:
		DibujadorInicio(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar() override;
		~DibujadorInicio();

};

#endif /* SRC_APP_DIBUJADORINICIO_H_ */
