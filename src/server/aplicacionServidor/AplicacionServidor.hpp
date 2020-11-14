#ifndef SRC_SERVER_APLICACIONSERVIDOR_APLICACIONSERVIDOR_HPP_
#define SRC_SERVER_APLICACIONSERVIDOR_APLICACIONSERVIDOR_HPP_

#include <SDL2/SDL.h>

#include <list>

#include "../../log/Log.hpp"

#include "../../lector/ArchivoLeido.hpp"
#include "../../modelo/Nivel.hpp"
#include "../../modelo/Juego.hpp"

class AplicacionServidor{
	public:
		AplicacionServidor(list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla);
		~AplicacionServidor();

		void iniciarJuego();
		void gameLoop();

	private:
		void revisarSiTerminoNivel(list<Mario*> jugadores);
		SDL_Rect* obtenerRectCamara();
		void moverCamara(list<Mario*> jugadores);
		Log* log;
		Juego* juego;
		SDL_Rect rectanguloCamara;
		int tiempoDeInicio;
		int tiempoFaltante;
		int cantJugadores;
		int ancho_pantalla;
		bool terminoElJuego;
		bool comenzoElJuego;
		bool ganaron;
		bool juegoInicializadoCorrectamente;
};



#endif /* SRC_SERVER_APLICACIONSERVIDOR_APLICACIONSERVIDOR_HPP_ */
