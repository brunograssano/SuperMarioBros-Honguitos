#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <sstream>

#include "SpriteMario.h"


const int ANCHO_IMAGEN_PIXEL = 405;
const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_SPRITE_PIXEL = 16;
const int ALTO_SPRITE_PIXEL = 32;
const int PASO_PROXIMO_SPRITE = 30;
const int CANT_DE_EVENTOS_MAX = 10;

SpriteMario::SpriteMario(string direccionImagen){
	direccionTextura = direccionImagen;
	estadoActual = 7;
	proximoEstado = 7;
	int corrimientoEnImagen = 0;

	// Variables que controlan el cambio de Sprite
	contadorEvento = 0;
	temporizadorMarioAgachado = 0;

	for(int i=0;i<14;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = ANCHO_SPRITE_PIXEL;
		estadosPosibles[i].h = ALTO_SPRITE_PIXEL;
		corrimientoEnImagen+= PASO_PROXIMO_SPRITE;
	}
}

SDL_Rect SpriteMario::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}

bool SpriteMario::controlDeFlujoSprite() {

    bool estabaQuieto = estadoActual == 6 || estadoActual == 7;

    if (estabaQuieto) { return estabaQuieto; }

    if (++contadorEvento < CANT_DE_EVENTOS_MAX) { return false; }

    contadorEvento = 0;

    return true;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++ ACTUALIZAR ESTADO DE MARIO SEGUN EL EVENTO ++++++++++++++*/
/* Se actualiza estado segun corresponda luego de presionar LEFT o RIGTH */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

bool SpriteMario::estaCorriendo(Mario* mario, bool btnDerecho) {

    bool corriendo = false;

    /* Corriendo hacia la izquierda, Estados permitidos: 3, 4 y 5 */
    if (estadoActual >= 2 && estadoActual < 7) {
        corriendo = true;

        // Cuando la funcion controlDeFlujoSprite devuelve "true", se permite el cambio de sprite.
        if (!controlDeFlujoSprite()) { return corriendo; }

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
    else if (estadoActual > 6 && estadoActual <= 11) {
        corriendo = true;

        // Cuando la funcion controlDeFlujoSprite devuelve "true", se permite el cambio de sprite.
        if (!controlDeFlujoSprite()) { return corriendo; }

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
		cambiandoDirecc = true;
		estadoActual = 2;
		proximoEstado = 7;
	}
	else if (caminandoADer && !btnDerecho) {
	    cambiandoDirecc = true;
        estadoActual = 11;
        proximoEstado = 6;
	}

	/* Mario quieto */
	else if (estadoActual == 6 && btnDerecho) {
		cambiandoDirecc = true;
		if (!controlDeFlujoSprite()) { return cambiandoDirecc; }
		estadoActual = 7;
		proximoEstado = 7;
	}
	else if (estadoActual == 7 && !btnDerecho) {
		cambiandoDirecc = true;
		if (!controlDeFlujoSprite()) { return cambiandoDirecc; }
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
    	estadoActual = 12;
    	proximoEstado = 12;
    }

    else if (btnDerecho && mario->estaEnElPiso()) {
    	estadoActual = 7;
    	proximoEstado = 8;

    }

    else if (!btnDerecho && !mario->estaEnElPiso()) {
    	estadoActual = 1;
    	proximoEstado = 1;
    }

    else if (!btnDerecho && mario->estaEnElPiso()) {
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
	}

	if (!btnDerecho && agachado && mario->estaEnElPiso()) {

		estadoActual = 6;
		proximoEstado = 5;
	}

	return agachado;
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++ ACTUALIZAR ESTADO DE MARIO +++++++++++++++++++++*/
/*       Se actualiza estado cuando no se produce ningun evento         */
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
            if(!controlDeFlujoSprite()) {return cambiandoDirecc;}
            estadoActual = 8;
            proximoEstado = 9;
        } else {
            if(!controlDeFlujoSprite()) {return cambiandoDirecc;}
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
        }
        else {
            estadoActual = proximoEstado;
            proximoEstado--;
            if (proximoEstado == 2) { proximoEstado = 5; }
        }
    }

    // CORIIENDO HACIA LA DERECHA
    if (estadoActual > 6 && estadoActual < 11) {
        corriendo = true;
        if (mario->estaQuietoX()) {
            estadoActual = 7;
            proximoEstado = 7;
        }
        else {
            estadoActual = proximoEstado;
            proximoEstado++;
            if (proximoEstado == 11) { proximoEstado = 8; }
        }
    }

    return corriendo;

}

bool SpriteMario::estaAgachado(Mario* mario) {
    bool estaAgachado = estadoActual == 13 || estadoActual == 0;

    if (!estaAgachado) {
        temporizadorMarioAgachado = 0;
        return estaAgachado;
    }

    if(++temporizadorMarioAgachado < 3 ) { return estaAgachado; }

    temporizadorMarioAgachado = 0;

    if (estadoActual == 13 && mario->estaQuietoX() && mario->estaEnElPiso()) {
        estadoActual = 7; proximoEstado = 7;
    }

    if (estadoActual == 0 && mario->estaQuietoX() && mario->estaEnElPiso()) {
        estadoActual = 6; proximoEstado = 6;
    }

    return estaAgachado;
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void SpriteMario::actualizarSprite(Mario* mario){

	if(estaSaltando(mario)) { return; }

    if (!controlDeFlujoSprite()) { return; }

    if (estaAgachado(mario)) {return; }

    if(estaCambiandoDeDireccion(mario)) { return; }

	estaCorriendo(mario);
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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

void SpriteMario::actualizarSpriteMarioSaltar() {

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

void SpriteMario::actualizarSpriteMarioAgacharse() {

    // Reinicia el temporizador
    temporizadorMarioAgachado = 0;

    if (estadoActual >= 7 && estadoActual <= 10) {
        estadoActual = 13;
        proximoEstado = 13;
    }
    if (estadoActual >= 3 && estadoActual <= 6) {
        estadoActual = 0;
        proximoEstado = 0;
    }
}
