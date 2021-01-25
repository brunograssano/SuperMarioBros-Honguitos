#ifndef SRC_APP_DIBUJADORGAMEOVER_H_
#define SRC_APP_DIBUJADORGAMEOVER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#include <string>
#include <sstream>

#include "src/Client/App/Dibujadores/Dibujador.hpp"
#include "src/Client/App/Dibujadores/Recortes/RecorteCoffinMario.hpp"

#include "src/Client/App/VentanaInicio/BotonConTexto.hpp"
#include "DibujadorPuntos.hpp"
#include "DibujadorCreditos.hpp"

class DibujadorGameOver : public Dibujador{

	public:
		DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla,JuegoCliente* juegoCliente);
        void dibujar()override;
        void agregarEventoDeClick(SDL_Event eventoClick) override;
		~DibujadorGameOver() override;

	private:
        RecorteCoffinMario spriteCoffinMario;
        BotonConTexto* botonIzquierdo;
        BotonConTexto* botonDerecho;
        SDL_Event eventoMouse{};
        DibujadorPuntos* dibujadorPuntos;
        DibujadorCreditos* dibujadorCreditos;
        JuegoCliente* juegoCliente;

        void dibujarTextoGameOver();
        void dibujarPuntosObtenidosEnNiveles();
        void dibujarCoffinMario();
};



#endif /* SRC_APP_DIBUJADORGAMEOVER_H_ */
