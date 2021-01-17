#ifndef SRC_CLIENT_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_
#define SRC_CLIENT_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_

using namespace std;
#include <string>
#include "../../Utils/log/Log.hpp"
#include "EstadoMusica.hpp"
#include "EstadoSonidos.hpp"
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class ReproductorMusica{
	public:
		static ReproductorMusica* getInstance();
		void ReproducirMusicaNivel(string nombreCancion);
        void reproducirSonido(const string& tipoSonido);
        void ponerMusica(const string& nombreCancion);
        static void reanudarMusica();
        static void pausarMusica();
		void cambiarMusica();
		void cambiarSonidos();
		~ReproductorMusica();


    private:
        EstadoMusica* estadoMusica;
        EstadoSonidos* estadoSonidos;
        static ReproductorMusica* reproductor;
        ReproductorMusica();
        map<string,Mix_Chunk*> efectosDeSonido;
        Mix_Music* cancionReproduciendose = nullptr;
};



#endif /* SRC_CLIENT_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_ */
