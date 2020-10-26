#ifndef SRC_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_
#define SRC_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_

using namespace std;
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class ReproductorMusica{
	public:
		static ReproductorMusica* getInstance();
		void ReproducirMusicaNivel(string nombreCancion);
		void ReproducirSonidoSalto();
	private:
		static ReproductorMusica* reproductor;
		ReproductorMusica(){
			if((Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)){
				// PONER ERROR EN LOG
			}
		}
};



#endif /* SRC_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_ */
