#ifndef SRC_CLIENT_APP_VENTANAINICIO_BOTONCONTEXTO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_BOTONCONTEXTO_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "OcultadorDeTexto.hpp"

class BotonConTexto
{
    private:

		SDL_Rect rectangulo{};
        std::string texto;
		SDL_Texture* texturaTexto;
		TTF_Font* fuente;
		SDL_Renderer* renderer;
		SDL_Texture* cargoTextura(const std::string& texto);
		bool clickeado;
		OcultadorDeTexto* ocultadorDeTexto;

    public:

		BotonConTexto( int posicionX, int posicionY, int ancho, int alto , const std::string& texto,SDL_Renderer* renderer,TTF_Font* fuente);

		void ocultaTexto();

		void cambiarTexto(const std::string& texto);

		bool botonClickeado(SDL_Event evento) const;

		void mostrarse();

		void mostrarseCambiandoAncho();

		void seleccionarCajaTexto();

		void deseleccionarCajaTexto();

		~BotonConTexto();
};

#endif
