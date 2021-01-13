#ifndef SRC_APP_DIBUJADORGANADORES_H_
#define SRC_APP_DIBUJADORGANADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>

#include "src/Client/app/Dibujadores/Dibujador.hpp"
#include "ParticulaGanadores.hpp"

#include "src/Client/app/juegoCliente/JuegoCliente.hpp"
#include "src/Client/app/Dibujadores/Recortes/Recorte.hpp"


class DibujadorGanadores : public Dibujador{
	public:
		DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar(JuegoCliente* juegoCliente);
		~DibujadorGanadores() override;

	private:
		void dibujarTextoGanadores(JuegoCliente* juegoCliente);
		void dibujarParticulas();
		void dibujarPersonajes();

		map<int, SDL_Color> colores;
        Recorte* spritePeach;
        Recorte* spriteToad;
        Recorte* spriteYoshi;
		list<ParticulaGanadores*> particulas;
};


#endif /* SRC_APP_DIBUJADORGANADORES_H_ */
