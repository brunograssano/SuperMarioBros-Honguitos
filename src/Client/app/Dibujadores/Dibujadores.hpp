#ifndef SRC_APP_DIBUJADORES_H_
#define SRC_APP_DIBUJADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#include "../juegoCliente/JuegoCliente.hpp"
#include "../CargadorTexturas.hpp"
#include "../../../Server/sprites/SpriteMario.hpp"

#include "src/Client/app/Dibujadores/DibujadoresFinales/DibujadorGameOver.hpp"
#include "src/Client/app/Dibujadores/DibujadoresJuego/DibujadorInicio.hpp"
#include "src/Client/app/Dibujadores/DibujadoresFinales/DibujadorGanadores.hpp"
#include "src/Client/app/Dibujadores/DibujadoresJuego/DibujadorJuego.hpp"
#include "src/Client/app/Dibujadores/DibujadoresError/DibujadorError.hpp"
#include "src/Client/app/Dibujadores/DibujadoresError/DibujadorErrorServidor.hpp"

class Dibujadores{

	public:
		Dibujadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla, bool leidoCorrectamente);
		void dibujarJuego(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente);
		void dibujarGameOver();
		void dibujarInicio();
		void dibujarPantallaGanadores(JuegoCliente* juegoCliente);
		void dibujarErrorServidor();
		~Dibujadores();

	private:
		DibujadorGameOver* dibujadorGameOver;
		DibujadorInicio* dibujadorInicio;
		DibujadorGanadores* dibujadorGanadores;
		DibujadorJuego* dibujadorJuego;
		DibujadorError* dibujadorError;
		DibujadorErrorServidor* dibujadorErrorServidor;
		bool archivoBienLeido;
};



#endif /* SRC_APP_DIBUJADORES_H_ */
