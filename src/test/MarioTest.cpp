#include "MarioTest.h"


void MarioTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas de Mario ==========" << endl;
	test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(testSuite);
	test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(testSuite);
	test03CuandoPedisAMarioQueSalteSeQuedaArriba(testSuite);
	test04CuandoMarioSeMueveParaAbajoBaja(testSuite);
	test05MarioEmpiezaConCeroMonedas(testSuite);
	test06MarioEmpiezaConCeroPuntos(testSuite);
	test07MarioGanaDiezPuntosYDevuelveEsoDeTotal(testSuite);
	test08CuandoMarioQuiereBajarPorDebajoDeSuNivelMinimoSuPosicionEnYesElMinimo(testSuite);
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

void MarioTest::test03CuandoPedisAMarioQueSalteSeQuedaArriba(Assert* testSuite){

	Mario* mario = new Mario();

	int posicion = mario->obtenerPosicionY();

	mario->moveraArriba();
	mario->actualizarPosicion();
	testSuite->assert(mario->obtenerPosicionY() > posicion,"Mario salta y queda arriba: ");

	delete mario;
}

void MarioTest::test04CuandoMarioSeMueveParaAbajoBaja(Assert* testSuite){

	Mario* mario = new Mario();
	mario->moveraArriba();
	mario->actualizarPosicion();
	mario->moveraArriba();
	mario->actualizarPosicion();
	int posicion = mario->obtenerPosicionY();

	mario->moveraAbajo();
	mario->actualizarPosicion();

	testSuite->assert(mario->obtenerPosicionY() < posicion,"Mario puede bajar: ");

	delete mario;
}

void MarioTest::test05MarioEmpiezaConCeroMonedas(Assert* testSuite){

	Mario* mario = new Mario();

	testSuite->assert(mario->obtenerMonedas(),0,"Mario empieza con 0 monedas: ");

	delete mario;
}

void MarioTest::test06MarioEmpiezaConCeroPuntos(Assert* testSuite){

	Mario* mario = new Mario();

	testSuite->assert(mario->obtenerPuntos(),0,"Mario empieza con 0 puntos: ");

	delete mario;
}

void MarioTest::test07MarioGanaDiezPuntosYDevuelveEsoDeTotal(Assert* testSuite){

	Mario* mario = new Mario();
	mario->agregarPuntos(10);

	testSuite->assert(mario->obtenerPuntos(),10,"Mario tiene 10 puntos: ");

	delete mario;
}

void MarioTest::test08CuandoMarioQuiereBajarPorDebajoDeSuNivelMinimoSuPosicionEnYesElMinimo(Assert* testSuite){
	Mario* mario = new Mario();
	float posicionInicial = mario->obtenerPosicionY();
	mario->moveraAbajo();
	mario->actualizarPosicion();
	testSuite->assert(mario->obtenerPosicionY(), posicionInicial, 1e-6,"Mario puede bajar: ");
	delete mario;
}
