#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <sstream>

#include "SpriteMario.h"
#include "../app/App.h"


const int ANCHO_IMAGEN_PIXEL = 405;
const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_SPRITE_PIXEL = 16;
const int ALTO_SPRITE_PIXEL = 32;
const int PASO_PROXIMO_SPRITE = 30;

SpriteMario::SpriteMario(string direccionImagen){
	direccionTextura = direccionImagen;
	estadoActual = 7;
	proximoEstado = 7;
	int corrimientoEnImagen = 0;
	for(int i=0;i<14;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = ANCHO_SPRITE_PIXEL;
		estadosPosibles[i].h = ALTO_SPRITE_PIXEL;
		corrimientoEnImagen+= PASO_PROXIMO_SPRITE;
	}
}

int SpriteMario::obtenerPosicionXRectangulo(){
	return estadosPosibles[estadoActual].x;
}

SDL_Rect SpriteMario::obtenerRectanguloActual(){
	return estadosPosibles[0];//Da lo mismo cual devolvamos aca, cambia a partir de donde estaria la imagen
}


int contador = 0; //TODO CAMBIAR ESTO QUE ES UN ASCO POR DIOS.
void SpriteMario::actualizarSprite(Mario* mario){
	if(contador < 15){
		contador++;
		return;
	}

	if(mario->estaQuietoX()){
		switch(estadoActual){

			case 0:
				break;
			case 1:
				if(mario->estaEnElPiso()){
					estadoActual = 6;
					proximoEstado = 6;
				}
				break;

			case 2:
				estadoActual = 7; proximoEstado = 7;
				break;

			case 3:
			case 4:
			case 5:
			case 6:
				estadoActual = 6; proximoEstado = 6;
				break;

			case 7:
			case 8:
			case 9:
			case 10:
				estadoActual = 7; proximoEstado = 7;
				break;

			case 11:
				estadoActual = 6; proximoEstado = 6;
				break;

			case 12:
				if(mario->estaEnElPiso()){
					estadoActual = 7;
					proximoEstado = 7;
				}
				break;

			case 13:
				break;
		}
	}else{
		estadoActual = proximoEstado;

		switch(estadoActual){
			case 0:
				break;

			case 1:
				if(mario->estaEnElPiso()){
					estadoActual = 5;
					proximoEstado = 4;
				}
				break;

			case 2:
				break;

			case 3: proximoEstado = 5;
				break;

			case 4: proximoEstado = 3;
				break;

			case 5: proximoEstado = 4;
				break;

			case 6:
				break;

			case 7:
				break;

			case 8: proximoEstado = 9;
				break;

			case 9: proximoEstado = 10;
				break;

			case 10: proximoEstado = 8;
				break;

			case 11:
				break;

			case 12:
				if(mario->estaEnElPiso()){
					estadoActual = 8;
					proximoEstado = 9;
				}
				break;

			case 13:
				break;
		}
	}
	contador = 0;
}

void SpriteMario::actualizarSpriteMarioDerecha(Mario* mario) {
	mario->aceleraraDerecha();
	switch(estadoActual){
		case 0:
		case 2:
			estadoActual = 7;
			proximoEstado = 8;
		break;
		case 1:
		case 4:
		case 5:
		case 6:
			estadoActual = 2;
			proximoEstado = 2;
		break;
		case 3:
			estadoActual = 7;
			proximoEstado = 8;
		break;
		case 7:
			estadoActual = 8;
			proximoEstado = 9;
		break;
		case 8:
			estadoActual = 9;
			proximoEstado = 10;
		break;
		case 9:
			estadoActual = 10;
			proximoEstado = 8;
		break;
		case 10:
			estadoActual = 8;
			proximoEstado = 9;
		break;
		case 11:
			estadoActual = 7;
			proximoEstado = 7;
		break;
		case 12:
			if(mario->estaEnElPiso()){
				estadoActual = 8;
				proximoEstado = 9;
			}else{
				estadoActual = 12;
				proximoEstado = 12;
			}
		break;
		case 13:
			estadoActual = 8;
			proximoEstado = 9;
		break;
	}
}

void SpriteMario::actualizarSpriteMarioIzquierda(Mario* mario) {
	mario->aceleraraIzquierda();

	switch(estadoActual){
		case 0:
			estadoActual = 5;
			proximoEstado = 6;
		break;
		case 1:
			if(mario->estaEnElPiso()){
				estadoActual = 5;
				proximoEstado = 4;
			}else{
				estadoActual = 1;
				proximoEstado = 1;
			}
			break;
		case 2:
			estadoActual = 6;
			proximoEstado = 6;
		break;
		case 3:
			estadoActual = 5;
			proximoEstado = 6;
			break;
		case 4:
			estadoActual = 3;
			proximoEstado = 5;
			break;
		case 5:
			estadoActual = 4;
			proximoEstado = 3;
			break;
		case 6:
			estadoActual = 5;
			proximoEstado = 4;
			break;
		case 7:
			estadoActual = 11;
			proximoEstado = 5;
			break;
		case 8:
		case 9:
		case 10:
			estadoActual = 11;
			proximoEstado = 11;
			break;
		case 11:
			estadoActual = 5;
			proximoEstado = 4;
			break;
		case 12:
			estadoActual = 11;
			proximoEstado = 11;
		break;
		case 13:
			estadoActual = 0;
			proximoEstado = 5;
		break;
	}
}

void SpriteMario::actualizarSpriteMarioSaltar(Mario* mario) {
    mario->saltar();
    if ((estadoActual >= 7 && estadoActual <= 10) || estadoActual == 13) {
        estadoActual = 12;
        proximoEstado = 12;
    }
    if ((estadoActual >= 3 && estadoActual <= 6) || estadoActual == 0) {
        estadoActual = 1;
        proximoEstado = 1;
    }
}

void SpriteMario::actualizarSpriteMarioAgacharse(Mario* mario) {
    if (estadoActual >= 7 && estadoActual <= 10) {
        estadoActual = 13;
        proximoEstado = 13;
    }
    if (estadoActual >= 3 && estadoActual <= 6) {
        estadoActual = 0;
        proximoEstado = 0;
    }
}
