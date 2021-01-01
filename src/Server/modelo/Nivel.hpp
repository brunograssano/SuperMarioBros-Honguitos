#ifndef SRC_SERVER_MODELO_NIVEL_HPP_
#define SRC_SERVER_MODELO_NIVEL_HPP_

#include <map>
#include <string>
#include<tuple>
#include <cstdlib>
#include <utility>

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
			this->direccionFondo = std::move(direccionFondo);
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

		int obtenerTiempo() const{
			return tiempo;
		}

		int obtenerMundo() const{
			return mundo;
		}

		void actualizarModelo();

		void inicializarPosicionEnemigo();
		void inicializarPosicionMonedas();

		void inicializarPosicionesOcupadasPorBloques();

		float obtenerPuntoBanderaFin() const;

		list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
		string obtenerDireccionFondoActual();

		~Nivel(){
			for(const auto& plataforma:plataformas){
				delete plataforma;
			}
			for(const auto& moneda:monedas){
				delete moneda;
			}
			for(const auto& enemigo:enemigos){
				delete enemigo;
			}
			plataformas.clear();
			enemigos.clear();
			monedas.clear();
		}


	private:

		void actualizarPosicionesEnemigos();
		void actualizarMonedas();

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



#endif /* SRC_SERVER_MODELO_NIVEL_HPP_ */
