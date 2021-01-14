#ifndef SRC_APP_DIBUJADORGANADORES_H_
#define SRC_APP_DIBUJADORGANADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Dibujador.hpp"
#include "ParticulaGanadores.hpp"

#include "../juegoCliente/JuegoCliente.hpp"

#include "../../../Server/sprites/spritesPersonajesSaltando/SpritePeachSaltando.hpp"
#include "../../../Server/sprites/spritesPersonajesSaltando/SpriteToadSaltando.hpp"
#include "../../../Server/sprites/spritesPersonajesSaltando/SpriteYoshiSaltando.hpp"

#include "src/Client/app/VentanaInicio/BotonConTexto.hpp"

class DibujadorGanadores : public Dibujador{
	public:
		DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar(JuegoCliente* juegoCliente);
		~DibujadorGanadores() override;

    void agregarEventoDeClick(SDL_Event eventoClick);

private:
		void dibujarTextoGanadores(JuegoCliente* juegoCliente);
        void dibujarPuntosTotales(JuegoCliente *juegoCliente);
		void dibujarParticulas();
		void dibujarPersonajes();
		void dibujarPuntos(JuegoCliente* juegoCliente);
		void dibujarTitulo();
        void dibujarPuntosDelNivel(JuegoCliente *juegoCliente);
        void disminuirNivelAMostrarPuntos(int ultimoNivel);
        void aumentarNivelAMostrarPuntos(int ultimoNivel);

		BotonConTexto* botonIzquierdo;
		BotonConTexto* botonDerecho;
		SDL_Event eventoMouse;
		int nivelAMostrarPuntos;

		map<int, SDL_Color> colores;
		SpritePeachSaltando* spritePeach;
		SpriteToadSaltando* spriteToad;
		SpriteYoshiSaltando* spriteYoshi;
		list<ParticulaGanadores*> particulas;

};


#endif /* SRC_APP_DIBUJADORGANADORES_H_ */
