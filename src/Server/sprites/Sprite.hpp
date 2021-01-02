#ifndef SRC_SERVER_SPRITES_SPRITE_HPP_
#define SRC_SERVER_SPRITES_SPRITE_HPP_


#include <string>
using namespace std;
#include <SDL2/SDL.h>


class Sprite{

	public:

		virtual string direccionImagen(){
			return direccionTextura;
		}

		virtual void actualizarSprite(){}

		virtual SDL_Rect obtenerRectanguloActual(){
			SDL_Rect rectangulo = {20,20,20,20};
			return rectangulo;
		};//ver como refactorizar

		int obtenerEstadoActual(){
			return estadoActual;
		}
		virtual ~Sprite(){};

	protected:
		string direccionTextura;
		int ciclos = 0;
		int estadoActual = 0;


};

#endif /* SRC_SERVER_SPRITES_SPRITE_HPP_ */
