#ifndef SRC_MODELO_BLOQUES_BLOQUE_H_
#define SRC_MODELO_BLOQUES_BLOQUE_H_

using namespace std;
#include <list>

#include "../Posicion.h"

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

    protected:
    	Posicion* posicion;
};

class Sorpresa : public Bloque{
    public:
		Sorpresa(int coordenadaX, int coordenadaY){
			this->posicion = new PosicionFija(coordenadaX, coordenadaY);
		}

        ~Sorpresa(){
        	delete this->posicion;
        }

};

class Ladrillo : public Bloque {
	public:
		Ladrillo(int coordenadaX, int coordenadaY){
			this->posicion = new PosicionFija(coordenadaX, coordenadaY);
		}

		~Ladrillo(){
			delete this->posicion;
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
