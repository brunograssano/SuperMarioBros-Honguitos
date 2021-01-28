#ifndef SRC_APP_DIBUJADORJUEGO_H_
#define SRC_APP_DIBUJADORJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>

#include "src/Client/App/CargadorTexturas.hpp"

#include "src/Client/App/JuegoCliente/JuegoCliente.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteMario.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteKoopa.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteGoomba.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteMoneda.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteBloque.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteBolaDeFuego.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteChispa.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteFlor.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteMonedaFlotante.hpp"

#include "src/Client/App/Dibujadores/Dibujador.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteTuberia.hpp"

class DibujadorJuego : public Dibujador{

	public:
		DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla,JuegoCliente* juegoCliente);
		void dibujar() override;
		~DibujadorJuego() override;

	private:
        std::stringstream textoDeTiempo;
        std::stringstream textoDeNivel;
        std::stringstream textoDePuntos;

        JuegoCliente* juegoCliente;
		SDL_Rect rectanguloCamara{};

		RecorteMario* recorteSpriteMario;
		RecorteGoomba* recorteSpriteGoomba;
		RecorteKoopa* recorteSpriteKoopa;
		RecorteMoneda* recorteSpriteMoneda;
		RecorteBloque* recorteSpriteBloque;
		RecorteTuberia* recorteSpriteTuberia;

		std::map<int, Recorte*> recortes;
        std::map<int, std::string> clavesEfectos;
        std::map<int, SDL_Color> colores;

		void dibujarEnemigos();
		void dibujarPlataformas();
		void dibujarMonedas();
		void dibujarMarios();
		void dibujarTexto();
        void dibujarTuberias();
        void dibujarPozos();
        void dibujarEfectos();
        static int obtenerEspaciado(int cantidadJugadores);
        void dibujarFondoPozos();
};

#endif /* SRC_APP_DIBUJADORJUEGO_H_ */
