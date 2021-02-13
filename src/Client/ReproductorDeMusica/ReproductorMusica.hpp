#ifndef SRC_CLIENT_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_
#define SRC_CLIENT_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_

#include <string>
#include "EstadoMusica.hpp"
#include "EstadoSonidos.hpp"
#include <map>
#include <SDL_mixer.h>

class ReproductorMusica{
	public:
		static ReproductorMusica* getInstance();
		void ReproducirMusicaNivel(std::string nombreCancion);
        void reproducirSonido(const uint8_t& tipoSonido);
        void ponerMusica(const std::string& nombreCancion);
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
        std::map<uint8_t, Mix_Chunk*> efectosDeSonido;
        Mix_Music* cancionReproduciendose = nullptr;
};



#endif /* SRC_CLIENT_REPRODUCTORDEMUSICA_REPRODUCTORMUSICA_HPP_ */
