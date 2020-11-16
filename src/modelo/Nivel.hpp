#ifndef SRC_MODELO_NIVEL_HPP_
#define SRC_MODELO_NIVEL_HPP_

#include <map>
#include <string>
#include<tuple>
#include <cstdlib>

#include "Bloques/Bloque.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Moneda.hpp"
using namespace std;

const int ANCHO_FONDO2 = 8177;
const int ALTO_NIVEL = 600;

class Nivel{


	public:
		Nivel(int mundo,string direccionFondo,int tiempo,int cantidadMonedas,int puntoBanderaFin){
			this->mundo = mundo;
			this->direccionFondo = direccionFondo;
			this->tiempo = tiempo;
			this->cantidadMonedas = cantidadMonedas;
			this->puntoBanderaFin = ANCHO_FONDO2* (float) puntoBanderaFin /100;
			this->altoNivel = ALTO_NIVEL;
		}

		void agregarPlataforma(Plataforma* unaPlataforma){
			plataformas.push_back(unaPlataforma);
		}

		void agregarEnemigo(Enemigo* unEnemigo){
			enemigos.push_back(unEnemigo);
		}

		void agregarMoneda(Moneda* unaMoneda){
			monedas.push_back(unaMoneda);
		}

		int obtenerTiempo(){
			return tiempo;
		}

		int obtenerMundo(){
			return mundo;
		}


		void inicializarPosicionEnemigo();
		void inicializarPosicionMonedas();

		void actualizarPosicionesEnemigos();

		void inicializarPosicionesOcupadasPorBloques();

		float obtenerPuntoBanderaFin();

		list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
		string obtenerDireccionFondoActual();

		~Nivel(){
			plataformas.clear();
			enemigos.clear();
			monedas.clear();
		}


	private:

		bool esUnaPosicionXValidaEnemigo(int coordenadaX);

		bool esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY);

		map<int, bool> posicionesOcupadasXEnemigos;

		map<tuple<int, int>, bool> posicionesOcupadas;

		list<Plataforma*> plataformas;
		list<Enemigo*> enemigos;
		list<Moneda*> monedas;

		int altoNivel;

		int mundo;
		string direccionFondo;
		int tiempo;
		int cantidadMonedas;
		float puntoBanderaFin;
};



#endif /* SRC_MODELO_NIVEL_HPP_ */
