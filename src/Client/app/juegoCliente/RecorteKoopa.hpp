#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_
#include <SDL2/SDL.h>

const int COLORES_KOOPA_POSIBLES = 4, ESTADOS_KOOPA = 6;

class RecorteKoopa{

	public:
		RecorteKoopa(){
			int corrimientoEnImagenX=0,corrimientoEnImagenY=0;
			for(int j=0;j<COLORES_KOOPA_POSIBLES;j++){
				for(int i=0;i<ESTADOS_KOOPA;i++){
					estadosPosibles[j][i].x = corrimientoEnImagenX;
					estadosPosibles[j][i].y = corrimientoEnImagenY;
					estadosPosibles[j][i].w = 16;
					estadosPosibles[j][i].h = 24;
					corrimientoEnImagenX+= 16;
				}
				corrimientoEnImagenX = 0;
				corrimientoEnImagenY += 24;
			}
		}

		SDL_Rect obtenerRecorte(int recorte,int tipoGoomba){
			return estadosPosibles[tipoGoomba][recorte];
		}

	private:
			SDL_Rect estadosPosibles[COLORES_KOOPA_POSIBLES][ESTADOS_KOOPA];
};




#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_ */
