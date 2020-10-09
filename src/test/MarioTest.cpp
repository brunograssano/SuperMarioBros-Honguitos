#include "MarioTest.h"


void MarioTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas de Mario ==========" << endl;
	test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(testSuite);
	test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(testSuite);
	test03CuandoPedisAMarioQueSalteSeQuedaArriba(testSuite);
	test04CuandoMarioSeMueveParaAbajoBaja(testSuite);
	cout << "========== Finalizando con las pruebas de Mario ==========" << endl;

}

void MarioTest::test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(Assert* testSuite){

	Mario* mario = new Mario();
	MovimientoDerecha* movimiento = new MovimientoDerecha(5);

	int posicion = mario->obtenerPosicionX();

	mario->mover(movimiento);

	testSuite->assert(mario->obtenerPosicionX(),posicion+5,"Mario se mueve a derecha");

	delete mario;
	delete movimiento;
}

void MarioTest::test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(Assert* testSuite){

	Mario* mario = new Mario();
	MovimientoIzquierda* movimiento = new MovimientoIzquierda(5);

	int posicion = mario->obtenerPosicionX();

	mario->mover(movimiento);

	testSuite->assert(mario->obtenerPosicionX(),posicion-5,"Mario se mueve a izquierda");

	delete mario;
	delete movimiento;
}

void MarioTest::test03CuandoPedisAMarioQueSalteSeQuedaArriba(Assert* testSuite){

	Mario* mario = new Mario();
	MovimientoArriba* movimiento = new MovimientoArriba(50);

	int posicion = mario->obtenerPosicionY();

	mario->mover(movimiento);

	testSuite->assert(mario->obtenerPosicionY(),posicion+50,"Mario salta y queda arriba: ");

	delete mario;
	delete movimiento;
}

void MarioTest::test04CuandoMarioSeMueveParaAbajoBaja(Assert* testSuite){

	Mario* mario = new Mario();
	MovimientoAbajo* movimiento = new MovimientoAbajo(30);

	int posicion = mario->obtenerPosicionY();

	mario->mover(movimiento);

	testSuite->assert(mario->obtenerPosicionY(),posicion-30,"Mario puede bajar: ");

	delete mario;
	delete movimiento;
}
