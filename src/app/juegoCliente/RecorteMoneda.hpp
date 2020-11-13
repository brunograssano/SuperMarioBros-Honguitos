#ifndef SRC_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_
#define SRC_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_

#include <SDL2/SDL.h>

class RecorteMoneda{
	public:
		RecorteMoneda(){
			int desplazamiento = 0;
			for(int i = 0; i < 4; i++){
				this->estadosPosibles[i].x = desplazamiento;
				this->estadosPosibles[i].y = 0;
				this->estadosPosibles[i].w = 16;
				this->estadosPosibles[i].h = 17;
				desplazamiento += 16;
			}
		}

		SDL_Rect obtenerRecorte(int recorte){
			return estadosPosibles[recorte];
		}

	private:
		SDL_Rect estadosPosibles[4];
};



#endif /* SRC_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_ */
