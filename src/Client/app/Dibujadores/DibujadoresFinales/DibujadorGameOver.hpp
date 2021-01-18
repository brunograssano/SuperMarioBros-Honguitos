#ifndef SRC_APP_DIBUJADORGAMEOVER_H_
#define SRC_APP_DIBUJADORGAMEOVER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#include <string>
#include <sstream>

#include "src/Client/app/Dibujadores/Dibujador.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteCoffinMario.hpp"

#include "src/Client/app/VentanaInicio/BotonConTexto.hpp"
#include "src/Client/app/Dibujadores/DibujadorPuntos.hpp"
#include "src/Client/app/Dibujadores/DibujadorCreditos.hpp"

class DibujadorGameOver : public Dibujador{

	public:
		DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar(JuegoCliente* juegoCliente);
        void agregarEventoDeClick(SDL_Event eventoClick);
		~DibujadorGameOver() override;

	private:
        RecorteCoffinMario spriteCoffinMario;
        BotonConTexto* botonIzquierdo;
        BotonConTexto* botonDerecho;
        SDL_Event eventoMouse;
        DibujadorPuntos* dibujadorPuntos;
        DibujadorCreditos* dibujadorCreditos;
};



#endif /* SRC_APP_DIBUJADORGAMEOVER_H_ */
