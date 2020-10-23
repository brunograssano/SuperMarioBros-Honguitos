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

/*+++++++++++++ ACTUALIZAR ESTADO DE MARIO SEGUN EL EVENTO ++++++++++++++*/
/* Se actualiza estado segun corresponda luego de presionar LEFT o RIGTH */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

bool SpriteMario::estaCorriendo(Mario* mario, bool btnDerecho) {

    bool corriendo = false;

    /* Corriendo hacia la izquierda, Estados permitidos: 3, 4 y 5 */
    if (estadoActual > 2 && estadoActual < 7) {
        corriendo = true;
        mario->aceleraraIzquierda();

        estadoActual--;
        proximoEstado = estadoActual - 1;

        /* Fuera de rango */
        if (estadoActual == 2) {
            estadoActual = 5;
			proximoEstado = 4;
        }
        if (proximoEstado == 2) { proximoEstado = 5; }
    }


    /* Corriendo hacia la derecha, Estados permitidos: 8, 9 y 10 */
    if (estadoActual > 6 && estadoActual < 11) {
        corriendo = true;
        mario->aceleraraDerecha();

        estadoActual++;
        proximoEstado = estadoActual + 1;

        /* Fuera de rango */
        if (estadoActual == 11) {
            estadoActual = 8;
			proximoEstado = 9;
        }
        if (proximoEstado == 11) { proximoEstado = 8; }

    }

    return corriendo;
}


bool SpriteMario::estaCambiandoDeDireccion(Mario* mario, bool btnDerecho) {
	bool cambiandoDirecc = false;

	bool caminandoAIzq = estadoActual > 2 && estadoActual < 6;
	bool caminandoADer = estadoActual > 7 && estadoActual < 11;

	/* Mario caminando */
	if (caminandoAIzq && btnDerecho) {
		mario->aceleraraDerecha();
		cambiandoDirecc = true;
		estadoActual = 2;
		proximoEstado = 7;
	}

	if (caminandoADer && !btnDerecho) {
		mario->aceleraraIzquierda();
		cambiandoDirecc = true;
		estadoActual = 11;
		proximoEstado = 6;
	}

	/* Mario quieto */
	if (estadoActual == 6 && btnDerecho) {
		cambiandoDirecc = true;
		estadoActual = 7;
		proximoEstado = 7;
	}

	if (estadoActual == 7 && !btnDerecho) {
		cambiandoDirecc = true;
		estadoActual = 6;
		proximoEstado = 6;
	}

    return cambiandoDirecc;
}

bool SpriteMario::estaSaltando(Mario* mario, bool btnDerecho) {

    bool saltando = false;

    if (estadoActual != 12 && estadoActual != 1 ) {
    	return saltando;
    }

	saltando = true;

    if (btnDerecho && !mario->estaEnElPiso()) {
    	mario->aceleraraDerecha();
    	estadoActual = 12;
    	proximoEstado = 12;
    }

    if (btnDerecho && mario->estaEnElPiso()) {
    	mario->aceleraraDerecha();
    	estadoActual = 7;
    	proximoEstado = 8;

    }

    if (!btnDerecho && !mario->estaEnElPiso()) {
    	mario->aceleraraIzquierda();
    	estadoActual = 1;
    	proximoEstado = 1;
    }

    if (!btnDerecho && mario->estaEnElPiso()) {
    	mario->aceleraraIzquierda();
    	estadoActual = 6;
    	proximoEstado = 5;
    }

    return saltando;
}


bool SpriteMario::estaAgachado(Mario* mario, bool btnDerecho) {
	bool agachado = estadoActual == 0 || estadoActual == 13;

	if (btnDerecho && agachado && mario->estaEnElPiso()) {

		estadoActual = 7;
		proximoEstado = 8;

		mario->aceleraraDerecha();
	}

	if (!btnDerecho && agachado && mario->estaEnElPiso()) {

		estadoActual = 6;
		proximoEstado = 5;

		mario->aceleraraIzquierda();
	}

	return agachado;
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++ ACTUALIZAR ESTADO DE MARIO +++++++++++++++++++++*/
/* Se actualiza estado cuando no se produce ningun evento               */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool SpriteMario::estaSaltando(Mario* mario) {
    bool saltando = estadoActual == 1 || estadoActual == 12;

    if(saltando && mario->estaQuietoX() && mario->estaEnElPiso()) {
        if (estadoActual == 1) {
            estadoActual = 6;
            proximoEstado = 6;
        }
        if (estadoActual == 12) {
            estadoActual = 7;
            proximoEstado = 7;
        }
    }

    if(saltando && !mario->estaQuietoX()) {
        estadoActual = proximoEstado;
        if(estadoActual == 1 && mario->estaEnElPiso()) {
            estadoActual = 5;
            proximoEstado = 4;
        }
        if(estadoActual == 12 && mario->estaEnElPiso()) {
            estadoActual = 8;
            proximoEstado = 9;
        }

    }
    return saltando;
}

bool SpriteMario::estaCambiandoDeDireccion(Mario* mario) {
    bool cambiandoDirecc = estadoActual == 2 || estadoActual == 11;

    if (cambiandoDirecc &&  mario->estaQuietoX()) {
        if (estadoActual == 2) {
            estadoActual = 7;
            proximoEstado = 7;
        } else {
            estadoActual = 6;
            proximoEstado = 6;
        }
    }
    if (cambiandoDirecc &&  !mario->estaQuietoX()) {
        if (estadoActual == 2) {
            estadoActual = 8;
            proximoEstado = 9;
        } else {
            estadoActual = 5;
            proximoEstado = 4;
        }
    }

    return cambiandoDirecc;
}

bool SpriteMario::estaCorriendo(Mario* mario) {
    bool corriendo = false;

    // CORRIENDO HACIA LA IZQUIERDA
    if (estadoActual > 2 && estadoActual < 7) {
        corriendo = true;
        if (mario->estaQuietoX()) {
            estadoActual = 6;
            proximoEstado = 6;
        } else {
            estadoActual = proximoEstado;
            proximoEstado--;
            if (proximoEstado == 3) { proximoEstado = 5; }
        }
    }

    // CORIIENDO HACIA LA DERECHA
    if (estadoActual > 6 && estadoActual < 11) {
        corriendo = true;
        if (mario->estaQuietoX()) {
            estadoActual = 7;
            proximoEstado = 7;
        } else {
            estadoActual = proximoEstado;
            proximoEstado++;
            if (proximoEstado == 11) { proximoEstado = 8; }
        }
    }

    return corriendo;

}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int contador = 0; //TODO CAMBIAR ESTO QUE ES UN ASCO POR DIOS.
void SpriteMario::actualizarSprite(Mario* mario){
	if(contador < 20){
		contador++;
		return;
	}

	contador = 0;

	if(estaSaltando(mario)) { return; }
	if(estaCambiandoDeDireccion(mario)) { return; }
	if(estaCorriendo(mario)) { return; }


}

void SpriteMario::actualizarSpriteMarioDerecha(Mario* mario) {

    if (estaAgachado(mario,true)) { return; }

    if (estaSaltando(mario,true)) { return; }

    if (estaCambiandoDeDireccion(mario,true)) { return; }

    if (estaCorriendo(mario, true)) { return; }
}

void SpriteMario::actualizarSpriteMarioIzquierda(Mario* mario) {

    if (estaAgachado(mario,false)) { return; }

    if (estaSaltando(mario,false)) { return; }

    if (estaCambiandoDeDireccion(mario,false)) { return; }

    if (estaCorriendo(mario,false)) { return; }
}

void SpriteMario::actualizarSpriteMarioSaltar(Mario* mario) {

    mario->saltar();
    if (estadoActual >= 7 && estadoActual <= 10) {
        estadoActual = 12;
        proximoEstado = 12;
    }

    if (estadoActual == 13) {
        estadoActual = 13;
        proximoEstado = 13;
    }

    if (estadoActual >= 3 && estadoActual <= 6) {
        estadoActual = 1;
        proximoEstado = 1;
    }

    if (estadoActual == 1) {
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
