#ifndef SRC_SERVER_SPRITES_SPRITE_HPP_
#define SRC_SERVER_SPRITES_SPRITE_HPP_


#include <string>
using namespace std;
#include <SDL2/SDL.h>


class Sprite{

	public:

		virtual void actualizarSprite() = 0;
		virtual SDL_Rect obtenerRectanguloActual() = 0;
		virtual ~Sprite(){};

        virtual int obtenerEstadoActual(){
            return estadoActual;
        }
        virtual string direccionImagen(){
            return direccionTextura;
        }
	protected:
		string direccionTextura;
		int ciclos = 0;
		int estadoActual = 0;


};

#endif /* SRC_SERVER_SPRITES_SPRITE_HPP_ */
