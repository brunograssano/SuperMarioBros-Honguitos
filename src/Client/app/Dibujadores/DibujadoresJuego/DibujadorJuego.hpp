#ifndef SRC_APP_DIBUJADORJUEGO_H_
#define SRC_APP_DIBUJADORJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

#include "src/Client/app/juegoCliente/JuegoCliente.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteMario.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteKoopa.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteGoomba.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteMoneda.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteBloque.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteBolaDeFuego.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteChispa.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteFlor.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteMonedaFlotante.hpp"

#include "src/Client/app/Dibujadores/Dibujador.hpp"
#include "src/Client/app/Dibujadores/Recortes/RecorteTuberia.hpp"

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
		RecorteTuberia* recorteSpriteTuberia;

		map<int, Recorte*> recortes;
		map<int, string> clavesEfectos;

		map<int, SDL_Color> colores;

		void dibujarEnemigos(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarPlataformas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarMonedas(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarMarios(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarTexto(JuegoCliente* juegoCliente);
        void dibujarTuberias(SDL_Rect *rectanguloCamara, JuegoCliente *juegoCliente);
        void dibujarPozos(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
        void dibujarEfectos(SDL_Rect *rectanguloCamara, JuegoCliente *juegoCliente);
};

#endif /* SRC_APP_DIBUJADORJUEGO_H_ */
