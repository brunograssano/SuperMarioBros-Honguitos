#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_

#include <SDL2/SDL.h>

const int ESTADOS_MONEDA = 4;

class RecorteMoneda{
	public:
		RecorteMoneda(){
			int desplazamiento = 0;
			for(int i = 0; i < ESTADOS_MONEDA; i++){
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



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_ */
