#ifndef SRC_SERVER_APLICACIONSERVIDOR_APLICACIONSERVIDOR_HPP_
#define SRC_SERVER_APLICACIONSERVIDOR_APLICACIONSERVIDOR_HPP_

#include <SDL2/SDL.h>

#include <list>

#include "../src/log/Log.hpp"

#include "../src/lector/ArchivoLeido.hpp"
#include "../src/modelo/Nivel.hpp"
#include "../src/modelo/Juego.hpp"

class AplicacionServidor{
	public:
		AplicacionServidor(list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla);
		~AplicacionServidor();

		void iniciarJuego();

		static void* gameLoop_helper(void* ptr){
			((AplicacionServidor*) ptr)->gameLoop();
			return NULL;
		}

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
