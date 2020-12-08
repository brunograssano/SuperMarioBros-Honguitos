#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_

#include <SDL2/SDL.h>

const int COLORES_GOOMBA_POSIBLES = 4, ESTADOS_GOOMBA = 3;

class RecorteGoomba{
	public:
		RecorteGoomba(){
			int corrimientoEnImagenX=0,corrimientoEnImagenY=0;
			for(int j=0;j<COLORES_GOOMBA_POSIBLES;j++){
				for(int i=0;i<ESTADOS_GOOMBA;i++){
					estadosPosibles[j][i].x = corrimientoEnImagenX;
					estadosPosibles[j][i].y = corrimientoEnImagenY;
					estadosPosibles[j][i].w = 16;
					estadosPosibles[j][i].h = 16;
					corrimientoEnImagenX+= 16;
				}
				corrimientoEnImagenX = 0;
				corrimientoEnImagenY += 16;
			}

		}
		SDL_Rect obtenerRecorte(int recorte,int tipoGoomba){
			return estadosPosibles[tipoGoomba][recorte];
		}
	private:
		SDL_Rect estadosPosibles[COLORES_GOOMBA_POSIBLES][ESTADOS_GOOMBA];

};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_ */
