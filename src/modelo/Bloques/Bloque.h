#ifndef SRC_MODELO_BLOQUES_BLOQUE_H_
#define SRC_MODELO_BLOQUES_BLOQUE_H_

using namespace std;
#include <list>
#include <string>

#include "../Posicion.h"
#include "../../sprites/Sprite.h"
#include "../../sprites/SpriteSorpresa.h"
#include "../../sprites/SpriteLadrillo.h"

const int LADO_BLOQUE_DEFAULT = 10;

class Bloque{
    public:

		virtual ~Bloque(){};

		int obtenerPosicionX(){
			return this->posicion->obtenerPosX();
		}
		int obtenerPosicionY(){
			return this->posicion->obtenerPosY();
		}

		Sprite* obtenerSprite(){
			return this->spriteBloque;
		}

    protected:
    	Posicion* posicion;
    	Sprite* spriteBloque;
};

class Sorpresa : public Bloque{
    public:
		Sorpresa(int coordenadaX, int coordenadaY){
			this->posicion = new PosicionFija(coordenadaX/40 *40, coordenadaY/40 *40); //ES HORRIBLE NO ME MATEN AHRE
			this->spriteBloque = new SpriteSorpresa();
		}

        ~Sorpresa(){
        	delete this->posicion;
        	delete this->spriteBloque;
        }

};

class Ladrillo : public Bloque {
	public:
		Ladrillo(int coordenadaX, int coordenadaY){
			this->posicion = new PosicionFija(coordenadaX/40 *40, coordenadaY/40 *40);
			this->spriteBloque = new SpriteLadrillo();
		}

		~Ladrillo(){
			delete this->posicion;
			delete this->spriteBloque;
		}
};

class Plataforma : public Bloque {
	public:
		Plataforma(){
		}

		void agregarBloque(Bloque* bloque){
			bloques.push_back(bloque);
		}

		list<Bloque*> obtenerBloques(){
			return this->bloques;
		}

		~Plataforma(){
			bloques.clear();
		}
	private:
		list<Bloque*> bloques;
};


#endif /* SRC_MODELO_BLOQUES_BLOQUE_H_ */
