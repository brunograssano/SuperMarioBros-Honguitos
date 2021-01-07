#ifndef SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_
#define SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <SDL2/SDL_ttf.h>
using namespace std;

class CargadorTexturas{

	public:
		explicit CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario(int idMario);
		SDL_Texture* obtenerTexturaFondo();
		SDL_Texture* obtenerTexturaPersonaje(const string& personaje);
        SDL_Texture* obtenerTextura(const string& clave);
		SDL_Texture* obtenerParticula(const string& particulaAsociada);
		SDL_Texture* cargarFuenteDeTextoATextura(const string& textoAMostrar, SDL_Renderer* renderizador, SDL_Color colorTexto);
		void cargarTexturasNiveles(map<int, string> direccionesNiveles, SDL_Renderer *renderizador,unsigned short mundo);
		void revisarSiCambioNivel(string direccionFondo);
		~CargadorTexturas();

private:
		string direccionFondoActual;
		map<int,SDL_Texture*> texturasMario;
        map<string,SDL_Texture*> texturas;
		SDL_Texture* texturaFondoActual = nullptr;
		SDL_Texture* texturaFuenteJuego = nullptr;
		SDL_Texture* texturaDefecto = nullptr;
		map<string,SDL_Texture*> texturasNiveles;
		map<string,SDL_Texture*> particulas;
		map<string,SDL_Texture*> texturasPersonajes;

		TTF_Font* fuenteJuego;

		static SDL_Texture* cargarTextura(const string& direccion, SDL_Renderer* renderizador);
		SDL_Texture* intentarCarga(const string& descripcion, const string& direccion, SDL_Renderer* renderizador);

};



#endif /* SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_ */
