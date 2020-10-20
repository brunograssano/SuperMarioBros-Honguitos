#ifndef SRC_APP_SPRITEMARIO_H_
#define SRC_APP_SPRITEMARIO_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../modelo/Juego.h"
#include "../app/CargadorTexturas.h"

class SpriteMario {

	public:
		//Initializes variables
		SpriteMario();

		SpriteMario(string direccionImagen);
		//Deallocates memory

		int obtenerPosicionXRectangulo();
		SDL_Rect obtenerRectanguloActual();

		void actualizarSprite(Mario* mario);

        void actualizarSpriteMarioDerecha (Mario* mario);
		void actualizarSpriteMarioIzquierda(Mario* mario);
		void actualizarSpriteMarioSaltar(Mario* mario);
        void actualizarSpriteMarioAgacharse(Mario* mario);

	private:
		string direccionTextura;
		SDL_Rect estadosPosibles[14];
		int estadoActual;
		int proximoEstado;
};


#endif /* SRC_APP_SPRITEMARIO_H_ */
