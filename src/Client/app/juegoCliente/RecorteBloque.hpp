#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_


#include <SDL2/SDL.h>

const int COLORES_BLOQUES_POSIBLES = 5, ESTADOS_BLOQUE = 5;

class RecorteBloque{
	public:
	RecorteBloque(){
			int corrimientoEnImagenX=0,corrimientoEnImagenY=0;
			for(int j=0;j<COLORES_BLOQUES_POSIBLES;j++){
				for(int i=0;i<ESTADOS_BLOQUE;i++){
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
		SDL_Rect obtenerRecorte(int recorte,int tipoBloque){
			return estadosPosibles[tipoBloque][recorte];
		}
	private:
		SDL_Rect estadosPosibles[COLORES_BLOQUES_POSIBLES][ESTADOS_BLOQUE];

};


#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_ */
