using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "../modelo/Mario.h"
//#include "../modelo/Movimientos/Movimiento.h"


int pruebasPasadas;
int pruebasTotales;

void ASSERT(int obtenido,int esperado,std::string textoExplicativo){
	cout << textoExplicativo << ": ";
	if(obtenido==esperado){
		cout << "todo bien" <<endl;
		pruebasPasadas++;
	}
	else{
		cout << "todo mal" <<endl;
	}
	pruebasTotales++;
}




void test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(){

	Mario* mario = new Mario();
	MovimientoDerecha* movimiento = new MovimientoDerecha(5);

	int posicion = mario->obtenerPosicionX();

	mario->mover(movimiento);

	ASSERT(mario->obtenerPosicionX(),posicion+5,"Mario se mueve a derecha");

	delete mario;
	delete movimiento;
}

void test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(){

	Mario* mario = new Mario();
	MovimientoIzquierda* movimiento = new MovimientoIzquierda(5);

	int posicion = mario->obtenerPosicionX();

	mario->mover(movimiento);

	ASSERT(mario->obtenerPosicionX(),posicion-5,"Mario se mueve a izquierda");

	delete mario;
	delete movimiento;
}

int main(){
	pruebasPasadas = 0;
	pruebasTotales = 0;
	test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve();
	test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve();

	cout << "Pasaron " << pruebasPasadas << " pruebas de "<< pruebasTotales <<endl;
	return 0;
}
