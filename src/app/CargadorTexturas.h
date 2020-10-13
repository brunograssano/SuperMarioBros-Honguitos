#ifndef SRC_APP_CARGADORTEXTURAS_H_
#define SRC_APP_CARGADORTEXTURAS_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class CargadorTexturas{

	public:
		CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario();
		SDL_Texture* obtenerTexturaMoneda();
		SDL_Texture* obtenerTexturaFondo();
		void actualizarSpriteMario(std::string direccion, SDL_Renderer* renderizador);
		~CargadorTexturas();


	private:
		SDL_Texture* texturaMario = NULL; // TODO van a ser un vector? (por las diferentes vistas que puede tomar)
		SDL_Texture* texturaMoneda = NULL;
		SDL_Texture* texturaLadrillo = NULL;
		SDL_Texture* texturaSorpresa = NULL;
		SDL_Texture* texturaFondo = NULL;

		SDL_Texture* cargarTextura(std::string direccion,SDL_Renderer* renderizador);

};



#endif /* SRC_APP_CARGADORTEXTURAS_H_ */
