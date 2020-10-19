
#ifndef SRC_SPRITES_SPRITE_H_
#define SRC_SPRITES_SPRITE_H_


#include <string>
using namespace std;
#include <SDL2/SDL.h>


class Sprite{

	public:

		virtual string direccionImagen(){
			return direccionTextura;
		}

		virtual int obtenerPosicionXRectangulo(){
			return 0;
		}

		virtual void actualizarSprite(){}

		virtual SDL_Rect obtenerRectanguloActual(){
			SDL_Rect rectangulo = {20,20,20,20};
			return rectangulo;
		};

		virtual ~Sprite(){};

	protected:
		string direccionTextura;


};



#endif /* SRC_SPRITES_SPRITE_H_ */
