#ifndef SRC_MODELO_NIVEL_H_
#define SRC_MODELO_NIVEL_H_

#include "Bloques/Bloque.h"
#include "Enemigos/Enemigo.h"
#include "Moneda.h"
#include <string>

class Nivel{


	public:
		Nivel(int mundo,string direccionFondo,int tiempo,int cantidadMonedas){
			this->mundo = mundo;
			this->direccionFondo = direccionFondo;
			this->tiempo = tiempo;
			this->cantidadMonedas = cantidadMonedas;
			for(int i=0; i<cantidadMonedas; i++){
				monedas.push_back(new Moneda(60*i, 300));
			}
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
		void actualizarPosicionesEnemigos();
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

		list<Plataforma*> plataformas;
		list<Enemigo*> enemigos;
		list<Moneda*> monedas;
		int mundo;
		string direccionFondo;
		int tiempo;
		int cantidadMonedas;
};



#endif /* SRC_MODELO_NIVEL_H_ */
