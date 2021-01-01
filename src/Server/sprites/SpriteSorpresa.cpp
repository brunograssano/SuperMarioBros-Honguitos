
#include "SpriteSorpresa.hpp"

SpriteSorpresa::SpriteSorpresa(){
	direccionTextura = "resources/Imagenes/Bloques/BloqueSorpresa.png";
	estadoActual = 0;
	ciclos=0;
	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = 0;
		estadosPosible.w = 16;
		estadosPosible.h = 16;
		corrimientoEnImagen+= 16;
	}
}

void SpriteSorpresa::actualizarSprite(){
	// Por ahora no se actualiza este sprite (queda en estado 0)
}

SDL_Rect SpriteSorpresa::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}
