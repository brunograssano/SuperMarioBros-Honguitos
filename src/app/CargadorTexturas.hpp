#ifndef SRC_APP_CARGADORTEXTURAS_HPP_
#define SRC_APP_CARGADORTEXTURAS_HPP_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <SDL2/SDL_ttf.h>
using namespace std;


const int MAX_IMAGEN_NIVELES = 30;

class CargadorTexturas{

	public:
		CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario(int idMario);
		SDL_Texture* obtenerTexturaMoneda();
		SDL_Texture* obtenerTexturaFondo();
		SDL_Texture* obtenerTexturaLadrillo();
		SDL_Texture* obtenerTexturaSorpresa();
		SDL_Texture* obtenerTexturaCoffinMario();
		SDL_Texture* obtenerTexturaFondoInicio();
		SDL_Texture* obtenerTexturaTitulo();
		SDL_Texture* obtenerTexturaFondoGameOver();

		SDL_Texture* obtenerTexturaEnemigo(string spriteDireccionEnemigo,SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaBloque(string spriteDireccionBloque,SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaFuente();
		SDL_Texture* obtenerTexturaPersonaje(string personaje);

		SDL_Texture* obtenerParticula(string particulaAsociada);

		SDL_Texture* cargarFuenteDeTextoATextura(string textoAMostrar, SDL_Renderer* renderizador);

		void cargarTexturasNiveles(string direccionesNiveles[MAX_IMAGEN_NIVELES],int cantidadFondosNiveles, SDL_Renderer* renderizador);
		void actualizarSpriteMario(string direccion, SDL_Renderer* renderizador);
		void revisarSiCambioNivel(SDL_Renderer* renderizador);

		~CargadorTexturas();


	private:
		string direccionFondoActual;

		map<int,SDL_Texture*> texturasMario;

		SDL_Texture* texturaMoneda = NULL;
		SDL_Texture* texturaLadrillo = NULL;
		SDL_Texture* texturaSorpresa = NULL;
		SDL_Texture* texturaFondoActual = NULL;
		SDL_Texture* texturaFuenteJuego = NULL;
		SDL_Texture* texturaCoffinMario = NULL;
		SDL_Texture* texturaFondoInicio = NULL;
		SDL_Texture* texturaTitulo = NULL;
		SDL_Texture* texturaFondoGameOver = NULL;
		SDL_Texture* texturaDefecto = NULL;
		map<string,SDL_Texture*> texturasEnemigos;
		map<string,SDL_Texture*> texturasBloques;
		map<string,SDL_Texture*> texturasNiveles;
		map<string,SDL_Texture*> particulas;
		map<string,SDL_Texture*> texturasPersonajes;

		TTF_Font* fuenteJuego;

		SDL_Texture* cargarTextura(string direccion,SDL_Renderer* renderizador);
		SDL_Texture* intentarCarga(string descripcion,string direccion, SDL_Renderer* renderizador);

		bool tengoTexturaCargadaEnMemoria(string spriteDireccionImagen, map<string,SDL_Texture*> texturas);


};



#endif /* SRC_APP_CARGADORTEXTURAS_HPP_ */
