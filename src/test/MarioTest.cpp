#include "MarioTest.h"

/*
void MarioTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas de Mario ==========" << endl;
	test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(testSuite);
	test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(testSuite);
	test03MarioEmpiezaConCeroMonedas(testSuite);
	test04MarioEmpiezaConCeroPuntos(testSuite);
	test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(testSuite);
	cout << "========== Finalizando con las pruebas de Mario ==========" << endl;

}

void MarioTest::test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(Assert* testSuite){

	Mario* mario = new Mario();

	int posicion = mario->obtenerPosicionX();

	mario->aceleraraDerecha();
	mario->actualizarPosicion();
	testSuite->assert(mario->obtenerPosicionX() > posicion,"Mario se mueve a derecha");

	delete mario;
}

void MarioTest::test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(Assert* testSuite){

	Mario* mario = new Mario();

	int posicion = mario->obtenerPosicionX();

	mario->aceleraraIzquierda();
	mario->actualizarPosicion();
	testSuite->assert(mario->obtenerPosicionX() < posicion,"Mario se mueve a izquierda");

	delete mario;
}

void MarioTest::test03MarioEmpiezaConCeroMonedas(Assert* testSuite){

	Mario* mario = new Mario();

	testSuite->assert(mario->obtenerMonedas(),0,"Mario empieza con 0 monedas: ");

	delete mario;
}

void MarioTest::test04MarioEmpiezaConCeroPuntos(Assert* testSuite){

	Mario* mario = new Mario();

	testSuite->assert(mario->obtenerPuntos(),0,"Mario empieza con 0 puntos: ");

	delete mario;
}

void MarioTest::test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(Assert* testSuite){

	Mario* mario = new Mario();
	mario->agregarPuntos(10);

	testSuite->assert(mario->obtenerPuntos(),10,"Mario tiene 10 puntos: ");

	delete mario;
}*/
