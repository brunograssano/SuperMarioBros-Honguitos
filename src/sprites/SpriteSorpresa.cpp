
#include "SpriteSorpresa.h"

SpriteSorpresa::SpriteSorpresa(){
	direccionTextura = "resources/BloqueSorpresa.png";
	estadoActual = 0;
	ciclos=0;
	cambio=false;
	int corrimientoEnImagen = 0;
	for(int i=0;i<5;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 16;
		estadosPosibles[i].h = 32;
		corrimientoEnImagen+= 16;
	}
}

void SpriteSorpresa::actualizarSprite(){
	// Por ahora no se actualiza este sprite (queda en estado 0)
}

string SpriteSorpresa::obtenerDireccionSprite(){
	return this->direccionTextura;
}

//ESTO YA NO ES NECESARIO
int SpriteSorpresa::obtenerPosicionXRectangulo(){
	return estadosPosibles[estadoActual].x;
}


SDL_Rect SpriteSorpresa::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}
