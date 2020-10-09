#ifndef SRC_MODELO_NIVEL_H_
#define SRC_MODELO_NIVEL_H_

#include "Bloques/Bloque.h"
#include "Enemigos/Enemigo.h"
#include "Moneda.h"

class Nivel{


	public:
		Nivel(){
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

		~Nivel(){
			plataformas.clear();
			enemigos.clear();
			monedas.clear();
		}


	private:

		list<Plataforma*> plataformas;
		list<Enemigo*> enemigos;
		list<Moneda*> monedas;


};



#endif /* SRC_MODELO_NIVEL_H_ */
