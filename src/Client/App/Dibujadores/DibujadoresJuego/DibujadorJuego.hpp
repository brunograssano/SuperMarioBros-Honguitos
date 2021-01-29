#ifndef SRC_APP_DIBUJADORJUEGO_H_
#define SRC_APP_DIBUJADORJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>

#include "src/Client/App/CargadorTexturas.hpp"
#include "src/Client/App/JuegoCliente/JuegoCliente.hpp"
#include "src/Client/App/Dibujadores/Recortes/Recorte.hpp"
#include "src/Client/App/Dibujadores/Dibujador.hpp"

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

		std::map<int, Recorte*> recortes;
        std::map<int, std::string> clavesTexturas;
        std::map<int, SDL_Color> colores;

		void dibujarMarios();
		void dibujarTexto();
        static int obtenerEspaciado(int cantidadJugadores);

        void dibujar(int claveEntidad);
        void dibujadorSimple(entidad_t entidad);
};

#endif /* SRC_APP_DIBUJADORJUEGO_H_ */
