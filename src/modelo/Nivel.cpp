

#include "Nivel.h"



void Nivel::actualizarPosicionesEnemigos(){
	//list<Enemigo*>::iterator iteradorEnemigos;

	/*for (iteradorEnemigos = enemigos.begin(); iteradorEnemigos != enemigos.end(); iteradorEnemigos++){
		iteradorEnemigos->actualizarPosicion();
	}*/
	for (auto const& enemigo : enemigos) {
	    enemigo->actualizarPosicion();
	}
}

list<Enemigo*> Nivel::obtenerEnemigos(){
	return enemigos;
}


