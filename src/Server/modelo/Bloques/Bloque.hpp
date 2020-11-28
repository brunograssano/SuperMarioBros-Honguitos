#ifndef SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_
#define SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_

using namespace std;
#include <list>
#include <string>

#include "../../../Utils/Utils.hpp"

#include "../Posicion.hpp"
#include "../../sprites/Sprite.hpp"
#include "../../sprites/SpriteSorpresa.hpp"
#include "../../sprites/SpriteLadrillo.hpp"

#define SORPRESA 0

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

		virtual bloque_t serializar(){return {0,0,0,0};};

		void ubicarEnPosicionDefault(){
			delete this->posicion;
			this->posicion = new PosicionFija(200, 200);
		}

    protected:
    	Posicion* posicion;
    	Sprite* spriteBloque;

		int normalizarCoordenadaIngresada(int coordenada){
			return (coordenada/40)*40;
		}
};

class Sorpresa : public Bloque{
    public:
		Sorpresa(int coordenadaX, int coordenadaY){
			int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
			int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);
			this->posicion = new PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
			this->spriteBloque = new SpriteSorpresa();
		}

		bloque_t serializar()override{
			bloque_t bloqueSerializado;
			bloqueSerializado.posX = posicion->obtenerPosX();
			bloqueSerializado.posY = posicion->obtenerPosY();
			bloqueSerializado.numeroRecorteX = spriteBloque->obtenerEstadoActual();
			bloqueSerializado.numeroRecorteY = SORPRESA;
			return bloqueSerializado;
		}

        ~Sorpresa(){
        	delete this->posicion;
        	delete this->spriteBloque;
        }

};

class Ladrillo : public Bloque {
	public:
		Ladrillo(int coordenadaX, int coordenadaY, int tipo){

			int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
			int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);

			posicion = new PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
			tipoLadrillo = tipo;
			spriteBloque = new SpriteLadrillo(tipo);
		}

		bloque_t serializar()override{
			bloque_t bloqueSerializado;
			bloqueSerializado.posX = posicion->obtenerPosX();
			bloqueSerializado.posY = posicion->obtenerPosY();
			bloqueSerializado.numeroRecorteX = spriteBloque->obtenerEstadoActual();
			bloqueSerializado.numeroRecorteY = tipoLadrillo;
			return bloqueSerializado;
		}

		~Ladrillo(){
			delete posicion;
			delete spriteBloque;
		}

	private:
		int tipoLadrillo;

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


#endif /* SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_ */
