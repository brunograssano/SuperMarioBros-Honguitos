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

		//Deallocates memory
		~SpriteMario();

        void actualizarSpriteMarioDerecha (Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador);

        void actualizarSpriteMarioQuieto(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador);
        void actualizarSpriteMarioAgacharse(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador);

		void actualizarSpriteMarioIzquierda(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador);
		void actualizarSpriteMarioSaltar(Mario* mario, CargadorTexturas* cargadorTextura, SDL_Renderer* renderizador);

	private:

		std::string spriteMario[14];
		int estadoActual;
		bool agachado;
		bool saltando;

};


#endif /* SRC_APP_SPRITEMARIO_H_ */
