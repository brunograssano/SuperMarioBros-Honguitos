#ifndef SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_
#define SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <SDL2/SDL_ttf.h>
using namespace std;


const int MAX_IMAGEN_NIVELES = 30;

class CargadorTexturas{

	public:
		explicit CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario(int idMario);
		SDL_Texture* obtenerTexturaMoneda();
		SDL_Texture* obtenerTexturaFondo();
		SDL_Texture* obtenerTexturaCoffinMario();
		SDL_Texture* obtenerTexturaFondoInicio();
		SDL_Texture* obtenerTexturaTitulo();
		SDL_Texture* obtenerTexturaFondoGameOver();
        SDL_Texture* obtenerTexturaCorazon();
		SDL_Texture* obtenerTexturaEnemigo(string spriteDireccionEnemigo,SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaBloque(string spriteDireccionBloque,SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaPersonaje(string personaje);

		SDL_Texture* obtenerParticula(string particulaAsociada);

		SDL_Texture* cargarFuenteDeTextoATextura(string textoAMostrar, SDL_Renderer* renderizador, SDL_Color colorTexto);

		void cargarTexturasNiveles(map<int,string> direccionesNiveles,int cantidadFondosNiveles, SDL_Renderer* renderizador, unsigned short mundos);
		void revisarSiCambioNivel(SDL_Renderer* renderizador, string direccionFondoActual);

		~CargadorTexturas();


    SDL_Texture *obtenerTexturaTuberia();

private:
		string direccionFondoActual;

		map<int,SDL_Texture*> texturasMario;

		SDL_Texture* texturaMoneda = nullptr;
		SDL_Texture* texturaLadrillo = nullptr;
		SDL_Texture* texturaSorpresa = nullptr;
		SDL_Texture* texturaFondoActual = nullptr;
		SDL_Texture* texturaFuenteJuego = nullptr;
		SDL_Texture* texturaCoffinMario = nullptr;
		SDL_Texture* texturaFondoInicio = nullptr;
		SDL_Texture* texturaTitulo = nullptr;
		SDL_Texture* texturaFondoGameOver = nullptr;
		SDL_Texture* texturaDefecto = nullptr;
        SDL_Texture* texturaTuberias = nullptr;
        SDL_Texture* texturaCorazon = nullptr;
		map<string,SDL_Texture*> texturasEnemigos;
		map<string,SDL_Texture*> texturasBloques;
		map<string,SDL_Texture*> texturasNiveles;
		map<string,SDL_Texture*> particulas;
		map<string,SDL_Texture*> texturasPersonajes;

		TTF_Font* fuenteJuego;

		SDL_Texture* cargarTextura(string direccion, SDL_Renderer* renderizador);
		SDL_Texture* intentarCarga(string descripcion, string direccion, SDL_Renderer* renderizador);

		bool tengoTexturaCargadaEnMemoria(string spriteDireccionImagen, map<string,SDL_Texture*> texturas);

};



#endif /* SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_ */
