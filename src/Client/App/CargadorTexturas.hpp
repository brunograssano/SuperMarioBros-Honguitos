#ifndef SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_
#define SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_

#define DIRECCION_BASE_NIVELES "resources/Imagenes/Niveles/"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <SDL2/SDL_ttf.h>

class CargadorTexturas{

	public:
		explicit CargadorTexturas(SDL_Renderer* renderizador);
		SDL_Texture* obtenerTexturaMario(int idMario);
		SDL_Texture* obtenerTexturaFondo();
		SDL_Texture* obtenerTextura(const std::string& clave);
		SDL_Texture* obtenerParticula(const std::string& particulaAsociada);
		SDL_Texture* cargarFuenteDeTextoATextura(const std::string& textoAMostrar, SDL_Renderer* renderizador, SDL_Color colorTexto);
		void cargarTexturasNiveles(std::map<int, std::string> direccionesNiveles, SDL_Renderer *renderizador,unsigned short mundo);
		void revisarSiCambioNivel(std::string nombreFondo);
		~CargadorTexturas();

        void alternarModoDiego(int id);

private:
        std::string direccionFondoActual;
        std::map<int,SDL_Texture*> texturasMario;
        std::map<std::string,SDL_Texture*> texturas;
		SDL_Texture* texturaFondoActual = nullptr;
		SDL_Texture* texturaFuenteJuego = nullptr;
		SDL_Texture* texturaDefecto = nullptr;
        std::map<std::string,SDL_Texture*> texturasNiveles;
        std::map<std::string,SDL_Texture*> particulas;
		TTF_Font* fuenteJuego;

        static void destruirTexturasEnMapa(const std::map<std::string, SDL_Texture *>& mapaDeTexturas);
        void revisarCargaCorrecta(const std::map<std::string, SDL_Texture *>& texturasCargadas);
};



#endif /* SRC_CLIENT_APP_CARGADORTEXTURAS_HPP_ */
