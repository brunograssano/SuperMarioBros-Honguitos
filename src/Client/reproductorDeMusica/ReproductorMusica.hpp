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
		void ReproducirSonidoSalto();
		void ReproducirSonidoAgarrarMoneda();
		void ReproducirSonidoInicioJuego();
		void ReproducirSonidoSumarVida();
		void ReproducirSonidoRomperBloque();
		void ReproducirSonidoMarioMataGoomba();
		void ReproducirSonidoMarioChicoGolpeaLadrillo();
		void ReproducirSonidoMarioLanzaFuego();
		void ReproducirSonidoBandera();
		void ReproducirSonidoAparecePlanta();
		void ReproducirSonidoMarioAgarraHongo();
		void ReproducirSonidoApareceHongo();
		void ReproducirSonidoMarioPisaKoopa();
        void reproducirSonido(string tipoSonido);
        void ponerMusica(string nombreCancion);
        void reanudarMusica();
        void pausarMusica();
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
