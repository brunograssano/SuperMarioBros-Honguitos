#ifndef SRC_APP_SPRITEMARIO_H_
#define SRC_APP_SPRITEMARIO_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../modelo/Juego.h"
#include "../app/CargadorTexturas.h"

class SpriteMario : public Sprite{

	public:
		//Initializes variables
		SpriteMario();

		SpriteMario(string direccionImagen);
		//Deallocates memory

		int obtenerPosicionXRectangulo();
		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite(Mario* mario);

        void actualizarSpriteMarioDerecha (Mario* mario);
		void actualizarSpriteMarioIzquierda(Mario* mario);
		void actualizarSpriteMarioSaltar(Mario* mario);
        void actualizarSpriteMarioAgacharse(Mario* mario);

	private:
		SDL_Rect estadosPosibles[14];
		int estadoActual;
		int proximoEstado;

		bool estaCorriendo(Mario* mario, bool btnDerecho);
		bool estaSaltando(Mario* mario, bool btnDerecho);
		bool estaAgachado(Mario* mario, bool btnDerecho);
		bool estaCambiandoDeDireccion(Mario* mario, bool btnDerecho);

		bool estaCorriendo(Mario* mario);
		bool estaSaltando(Mario* mario);
		bool estaAgachado(Mario* mario);
		bool estaCambiandoDeDireccion(Mario* mario);
};

#endif /* SRC_APP_SPRITEMARIO_H_ */
