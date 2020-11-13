#ifndef SRC_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_
#define SRC_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_
#include <SDL2/SDL.h>

class RecorteKoopa{

	public:
		RecorteKoopa(){
			int corrimientoEnImagen=0;
			for(int i=0;i<6;i++){
				estadosPosibles[i].x = corrimientoEnImagen;
				estadosPosibles[i].y = 0;
				estadosPosibles[i].w = 16;
				estadosPosibles[i].h = 24;
				corrimientoEnImagen+= 16;
			}
		}

		SDL_Rect obtenerRecorte(int recorte){
			return estadosPosibles[recorte];
		}

	private:
			SDL_Rect estadosPosibles[6];
};




#endif /* SRC_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_ */
