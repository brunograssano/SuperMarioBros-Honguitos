#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMARIO_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMARIO_HPP_

#include <SDL2/SDL.h>

class RecorteMario{
	public:
		RecorteMario();
		SDL_Rect obtenerRecorte(int recorte);
	private:
		SDL_Rect estadosPosibles[14];
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMARIO_HPP_ */
