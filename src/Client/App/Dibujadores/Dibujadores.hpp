#ifndef SRC_APP_DIBUJADORES_H_
#define SRC_APP_DIBUJADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <map>
#include "../JuegoCliente/JuegoCliente.hpp"
#include "../CargadorTexturas.hpp"
#include "Dibujador.hpp"

class Dibujadores{

	public:
		Dibujadores(char direccionesFondoNiveles[MAX_CANT_NIVELES][MAX_LARGO_NOMBRE_NIVEL],unsigned short cantidadFondosNiveles,
              unsigned short mundo,unsigned short  ancho_pantalla,unsigned short  alto_pantalla,JuegoCliente *juegoCliente);
		void agregarEventoADibujadores(SDL_Event eventoClick);
        void dibujar();
		~Dibujadores();

        void comenzoElJuego();
        void ocurrioErrorEnServidor();
        void determinarEstado();

    void alternarModoDiego();

private:
        CargadorTexturas *cargadorTexturas;
        SDL_Renderer *renderizador;
        SDL_Window* ventanaAplicacion;
        std::map<int,std::string> direccionesNiveles;
        JuegoCliente *juegoCliente;
        std::map<std::string,Dibujador*> dibujadores;
        std::string estadoActual;

};



#endif /* SRC_APP_DIBUJADORES_H_ */
