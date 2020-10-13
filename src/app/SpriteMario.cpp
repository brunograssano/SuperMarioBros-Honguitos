#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <sstream>

#include "SpriteMario.h"
#include "App.h"

SpriteMario::SpriteMario() {
	//Initialize
	spriteMario[0]  = "./resources/sprite_mario_grande/mario_grande_agachado_izq.png";
	spriteMario[1]  = "./resources/sprite_mario_grande/mario_grande_saltando_izq.png";
	spriteMario[2]  = "./resources/sprite_mario_grande/mario_grande_frenando_izq.png";
	spriteMario[3]  = "./resources/sprite_mario_grande/mario_grande_caminando_izq_3.png";
	spriteMario[4]  = "./resources/sprite_mario_grande/mario_grande_caminando_izq_2.png";
	spriteMario[5]  = "./resources/sprite_mario_grande/mario_grande_caminando_izq_1.png";
	spriteMario[6]  = "./resources/sprite_mario_grande/mario_grande_quieto_izq.png";
	spriteMario[7]  = "./resources/sprite_mario_grande/mario_grande_quieto_der.png";
	spriteMario[8]  = "./resources/sprite_mario_grande/mario_grande_caminando_der_1.png";
	spriteMario[9]  = "./resources/sprite_mario_grande/mario_grande_caminando_der_2.png";
	spriteMario[10] = "./resources/sprite_mario_grande/mario_grande_caminando_der_3.png";
	spriteMario[11] = "./resources/sprite_mario_grande/mario_grande_frenando_der.png";
	spriteMario[12] = "./resources/sprite_mario_grande/mario_grande_saltando_der.png";
	spriteMario[13] = "./resources/sprite_mario_grande/mario_grande_agachado_der.png";

	estadoActual = 7;
	agachado = false;
	saltando = false;
}

SpriteMario::~SpriteMario() {
	//Deallocate
}

void SpriteMario::actualizarSpriteMarioQuieto(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador) {

    if (estadoActual >= 7 && estadoActual <= 10){
        estadoActual = 7;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);

    }
    else if (estadoActual <= 6 && estadoActual >= 3){
        estadoActual = 6;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);

    }
    agachado = false;
    saltando = false;
}



void SpriteMario::actualizarSpriteMarioDerecha(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador) {
	mario->aceleraraDerecha();

    if (estadoActual >= 7 && estadoActual < 10) {
		estadoActual++;
		cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
	}

	else if (estadoActual == 10) {
        estadoActual = 7;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
    }

	else if (estadoActual < 7) {
        estadoActual = 11;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
        estadoActual = 7;
	}
}

void SpriteMario::actualizarSpriteMarioIzquierda(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador) {
	mario->aceleraraIzquierda();

    if (estadoActual == 3) {
        estadoActual = 6;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
    }

    else if (estadoActual <= 6 && estadoActual > 3) {
		estadoActual--;
		cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
	}

	else if (estadoActual > 6) {
        estadoActual = 2;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
        estadoActual = 6;
	}
}




void SpriteMario::actualizarSpriteMarioSaltar(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador) {
    mario->saltar();
    if (estadoActual >= 7 && estadoActual <= 10) {
        estadoActual = 12;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
        estadoActual = 7;
    }
    if (estadoActual >= 3 && estadoActual <= 6) {
        estadoActual = 12;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
        estadoActual = 7;
    }
}

void SpriteMario::actualizarSpriteMarioAgacharse(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador) {
    mario->moveraAbajo();
    if (estadoActual >= 7 && estadoActual <= 10) {
        estadoActual = 13;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
        estadoActual = 7;
    }
    if (estadoActual >= 3 && estadoActual <= 6) {
        estadoActual = 13;
        cargadorTextura->actualizarSpriteMario(spriteMario[estadoActual],renderizador);
        estadoActual = 7;
    }
}
