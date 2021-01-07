#ifndef SRC_APP_DIBUJADORJUEGO_H_
#define SRC_APP_DIBUJADORJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#include "../juegoCliente/JuegoCliente.hpp"
#include "../juegoCliente/RecorteMario.hpp"
#include "../juegoCliente/RecorteKoopa.hpp"
#include "../juegoCliente/RecorteGoomba.hpp"
#include "../juegoCliente/RecorteMoneda.hpp"
#include "../juegoCliente/RecorteBloque.hpp"

#include "Dibujador.hpp"
#include "src/Client/app/juegoCliente/RecorteTuberia.hpp"

class DibujadorJuego : public Dibujador{

	public:
		DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);

		void dibujar(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujar() override{}
		~DibujadorJuego() override;

	private:
		stringstream textoDeTiempo;
		stringstream textoDeNivel;
		stringstream textoDePuntos;

		SDL_Rect rectanguloCamara{};

		RecorteMario* recorteSpriteMario;
		RecorteGoomba* recorteSpriteGoomba;
		RecorteKoopa* recorteSpriteKoopa;
		RecorteMoneda* recorteSpriteMoneda;
		RecorteBloque* recorteSpriteBloque;
		RecorteTuberia *recorteSpriteTuberia;

		map<int, SDL_Color> colores;

		void dibujarEnemigos(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarPlataformas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarMonedas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarMarios(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarTexto(JuegoCliente* juegoCliente);
        void dibujarTuberias(SDL_Rect *rectanguloCamara, JuegoCliente *juegoCliente);
};

#endif /* SRC_APP_DIBUJADORJUEGO_H_ */
