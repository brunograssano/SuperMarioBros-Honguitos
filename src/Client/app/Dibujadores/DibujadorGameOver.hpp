#ifndef SRC_APP_DIBUJADORGAMEOVER_H_
#define SRC_APP_DIBUJADORGAMEOVER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <sstream>

#include "Dibujador.hpp"
#include "../../../Server/sprites/Sprite.hpp"
#include "../../../Server/sprites/SpriteCoffinMario.hpp"
#include "src/Client/app/VentanaInicio/BotonConTexto.hpp"
#include "DibujadorPuntos.hpp"

class DibujadorGameOver : public Dibujador{

	public:
		DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar(JuegoCliente* juegoCliente);
        void agregarEventoDeClick(SDL_Event eventoClick);
		~DibujadorGameOver() override;

	private:
		SpriteCoffinMario* spriteCoffinMario;
        BotonConTexto* botonIzquierdo;
        BotonConTexto* botonDerecho;
        SDL_Event eventoMouse;
        DibujadorPuntos* dibujadorPuntos;
};



#endif /* SRC_APP_DIBUJADORGAMEOVER_H_ */
