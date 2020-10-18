#ifndef SRC_APP_CARGADORTEXTURAS_H_
#define SRC_APP_CARGADORTEXTURAS_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "../sprites/Sprite.h"
using namespace std;

class CargadorTexturas{

	public:
		CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario();
		SDL_Texture* obtenerTexturaMoneda();
		SDL_Texture* obtenerTexturaFondo();

		SDL_Texture* obtenerTexturaEnemigo(Sprite* spriteEnemigo,SDL_Renderer* renderizador);


		void actualizarSpriteMario(std::string direccion, SDL_Renderer* renderizador);
		void revisarSiCambioNivel(SDL_Renderer* renderizador);

		~CargadorTexturas();


	private:
		string direccionFondoActual;
		SDL_Texture* texturaMario = NULL; // TODO van a ser un vector? (por las diferentes vistas que puede tomar)
		SDL_Texture* texturaMoneda = NULL;
		SDL_Texture* texturaLadrillo = NULL;
		SDL_Texture* texturaSorpresa = NULL;
		SDL_Texture* texturaFondoActual = NULL;
		map<string,SDL_Texture*> texturasEnemigos;
		SDL_Texture* cargarTextura(std::string direccion,SDL_Renderer* renderizador);
		bool tengoTexturaCargadaEnMemoria(Sprite* spriteEnemigo);

};



#endif /* SRC_APP_CARGADORTEXTURAS_H_ */
