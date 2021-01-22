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

#include "src/Client/app/VentanaInicio/BotonConTexto.hpp"
#include "DibujadorPuntos.hpp"
#include "DibujadorCreditos.hpp"

class DibujadorGanadores : public Dibujador{
	public:
		DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla,JuegoCliente* juegoCliente);
		void dibujar()override;
		~DibujadorGanadores() override;
        void agregarEventoDeClick(SDL_Event eventoClick) override;

    private:
		void dibujarTextoGanadores();
		void dibujarParticulas();
		void dibujarPersonajes();
		void dibujarTitulo(const string& nombreGanador);

		BotonConTexto* botonIzquierdo;
		BotonConTexto* botonDerecho;
		SDL_Event eventoMouse{};
        JuegoCliente* juegoCliente;

        Recorte* spritePeach;
        Recorte* spriteToad;
        Recorte* spriteYoshi;
		list<ParticulaGanadores> particulas;
		DibujadorPuntos* dibujadorPuntos;
		DibujadorCreditos* dibujadorCreditos;
};


#endif /* SRC_APP_DIBUJADORGANADORES_H_ */
