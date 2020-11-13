#ifndef SRC_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_
#define SRC_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_

#include <SDL2/SDL.h>

class RecorteGoomba{
	public:
		RecorteGoomba(){
			int corrimientoEnImagen = 0;
			for(int i=0;i<3;i++){
				estadosPosibles[i].x = corrimientoEnImagen;
				estadosPosibles[i].y = 0;
				estadosPosibles[i].w = 16;
				estadosPosibles[i].h = 16;
				corrimientoEnImagen+= 16;
			}
		}
		SDL_Rect obtenerRecorte(int recorte){
			return estadosPosibles[recorte];
		}
	private:
		SDL_Rect estadosPosibles[3];
};



#endif /* SRC_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_ */
