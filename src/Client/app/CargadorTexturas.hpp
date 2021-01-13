#ifndef SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_
#define SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_

#define DIRECCION_BASE_NIVELES "resources/Imagenes/Niveles/"

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
		SDL_Texture* obtenerTextura(const string& clave);
		SDL_Texture* obtenerParticula(const string& particulaAsociada);
		SDL_Texture* cargarFuenteDeTextoATextura(const string& textoAMostrar, SDL_Renderer* renderizador, SDL_Color colorTexto);
		void cargarTexturasNiveles(map<int, string> direccionesNiveles, SDL_Renderer *renderizador,unsigned short mundo);
		void revisarSiCambioNivel(string nombreFondo);
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
		TTF_Font* fuenteJuego;

    static void destruirTexturasEnMapa(const map<string, SDL_Texture *>& mapaDeTexturas);

    void revisarCargaCorrecta(map<string, SDL_Texture *> texturasCargadas);
};



#endif /* SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_ */
