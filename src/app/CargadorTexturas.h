#ifndef SRC_APP_CARGADORTEXTURAS_H_
#define SRC_APP_CARGADORTEXTURAS_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "../sprites/Sprite.h"
#include <SDL2/SDL_ttf.h>
using namespace std;

class CargadorTexturas{

	public:
		CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario();
		SDL_Texture* obtenerTexturaMoneda();
		SDL_Texture* obtenerTexturaFondo();
		SDL_Texture* obtenerTexturaLadrillo();
		SDL_Texture* obtenerTexturaSorpresa();
		SDL_Texture* obtenerTexturaCoffinMario();
		SDL_Texture* obtenerTexturaFondoGameOver();

		SDL_Texture* obtenerTexturaEnemigo(Sprite* spriteEnemigo,SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaBloque(Sprite* spriteBloque,SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaFuente();

		SDL_Texture* cargarFuenteDeTextoATextura(string textoAMostrar, SDL_Renderer* renderizador);

		void actualizarSpriteMario(std::string direccion, SDL_Renderer* renderizador);
		void revisarSiCambioNivel(SDL_Renderer* renderizador);

		~CargadorTexturas();


	private:
		string direccionFondoActual;
		SDL_Texture* texturaMario = NULL;
		SDL_Texture* texturaMoneda = NULL;
		SDL_Texture* texturaLadrillo = NULL;
		SDL_Texture* texturaSorpresa = NULL;
		SDL_Texture* texturaFondoActual = NULL;
		SDL_Texture* texturaFuenteJuego = NULL;
		SDL_Texture* texturaCoffinMario = NULL;
		SDL_Texture* texturaFondoGameOver = NULL;
		map<string,SDL_Texture*> texturasEnemigos;
		map<string,SDL_Texture*> texturasBloques;

		TTF_Font* fuenteJuego;

		SDL_Texture* cargarTextura(std::string direccion,SDL_Renderer* renderizador);
		bool tengoTexturaEnemigoCargadaEnMemoria(Sprite* spriteEnemigo);
		bool tengoTexturaBloqueCargadaEnMemoria(Sprite* spriteBloque);


};



#endif /* SRC_APP_CARGADORTEXTURAS_H_ */
