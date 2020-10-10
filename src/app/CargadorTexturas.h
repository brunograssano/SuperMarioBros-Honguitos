#ifndef SRC_APP_CARGADORTEXTURAS_H_
#define SRC_APP_CARGADORTEXTURAS_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class CargadorTexturas{

	public:
		CargadorTexturas();

		~CargadorTexturas();


	private:
		SDL_Texture* texturaMario = NULL; // TODO van a ser un vector? (por las diferentes vistas que puede tomar)
		SDL_Texture* texturaMoneda = NULL;
		SDL_Texture* texturaLadrillo = NULL;
		SDL_Texture* texturaSorpresa = NULL;


		SDL_Texture* cargarTextura(std::string direccion);

};



#endif /* SRC_APP_CARGADORTEXTURAS_H_ */
