#ifndef SRC_APP_APP_HPP_
#define SRC_APP_APP_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#include "Dibujadores/Dibujadores.hpp"
#include "juegoCliente/JuegoCliente.hpp"
#include "CargadorTexturas.hpp"
#include "../log/Log.hpp"
#include "../lector/ArchivoLeido.hpp"
#include "../reproductorDeMusica/ReproductorMusica.hpp"

const int ANCHO_FONDO = 8177;
const int MAX_IMAGEN_ENEMIGOS = 30,MAX_IMAGEN_BLOQUE = 30;
const int MAX_BLOQUES=200,MAX_ENEMIGOS=70,MAX_MONEDAS=70;

typedef struct info_partida{
	unsigned short cantidadJugadores;
	jugador_t jugadores[MAX_JUGADORES];
	string direccionesFondoNiveles[MAX_IMAGEN_NIVELES];
	unsigned short cantidadFondosNiveles;
	//string direccionesImagenEnemigos[MAX_IMAGEN_ENEMIGOS];
	//string direccionesImagenBloques[MAX_IMAGEN_BLOQUE];

	bool iniciadoCorrectamente;
	unsigned short anchoVentana;
	unsigned short altoVentana;
	unsigned short idPropio;
}info_partida_t;

typedef struct ronda{
	bloque_t bloques[MAX_BLOQUES];
	enemigo_t enemigos[MAX_ENEMIGOS];
	moneda_t monedas[MAX_MONEDAS];
	jugador_t jugadores[MAX_JUGADORES];
	int posXCamara;
	int tiempoFaltante;
}info_ronda_t;


class App{

	protected:
		App(info_partida_t informacion,TipoLog* tipoLog){
			Log* log = Log::getInstance(tipoLog);

			determinarDimensionesPantalla(informacion.anchoVentana,informacion.altoVentana);
			inicializarSDL(log);

			cargadorTexturas = new CargadorTexturas(renderizador);
			if(informacion.iniciadoCorrectamente){
				cargadorTexturas->cargarTexturasNiveles(informacion.direccionesFondoNiveles,informacion.cantidadFondosNiveles, renderizador);
			}
			rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};

			juegoInicializadoCorrectamente = informacion.iniciadoCorrectamente;

			juegoCliente = new JuegoCliente(informacion.cantidadJugadores,informacion.jugadores,informacion.idPropio);

			sePusoMusicaInicio = false;
			terminoElJuego = false;
			comenzoElJuego = false;
			ganaron = false;
			dibujador = new Dibujadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla,juegoInicializadoCorrectamente);

			log->mostrarMensajeDeInfo("Inicio del juego");

		}

		static App* aplicacion;
		CargadorTexturas* cargadorTexturas;
		SDL_Window* ventanaAplicacion;
		SDL_Renderer* renderizador;
		SDL_Rect rectanguloCamara;
		Dibujadores* dibujador;

		void inicializarSDL(Log* log);
		void determinarDimensionesPantalla(int posibleAnchoVentana,int posibleAltoVentana);

		JuegoCliente* juegoCliente;

		bool sePusoMusicaInicio;
		bool terminoElJuego;
		bool comenzoElJuego;
		bool ganaron;
		bool juegoInicializadoCorrectamente;

		int ancho_pantalla;
		int alto_pantalla;

	public:
		App(App &other) = delete;
		static App *getInstance();
		static App *getInstance(info_partida_t informacion,TipoLog* tipoLog);


		void actualizarServer(const Uint8 *keystate);
		void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);

		SDL_Renderer* obtenerRenderizador();

		SDL_Rect* obtenerRectCamara();
		void dibujar();
		~App();


};

#endif /* SRC_APP_APP_HPP_ */
