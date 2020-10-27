#ifndef SRC_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_
#define SRC_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_

using namespace std;
#include <string>
#include "../log/Log.h"
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class ReproductorMusica{
	public:
		static ReproductorMusica* getInstance();
		void ReproducirMusicaNivel(string nombreCancion);
		void ReproducirSonidoSalto();
		void ReproducirSonidoAgarrarMoneda();
		~ReproductorMusica();
	private:
		static ReproductorMusica* reproductor;
		ReproductorMusica();
		map<string,Mix_Chunk*> efectosDeSonido;
		Mix_Music* cancionReproduciendose = nullptr;
};



#endif /* SRC_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_ */
