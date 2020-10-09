#include "BloqueTest.h"

void BloqueTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas de bloque ==========" << endl;

	test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(testSuite);

	cout << "========== Finalizando con las pruebas de bloque ==========" << endl;
}

void BloqueTest::test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite){

	Bloque* bloque = new Ladrillo(3, 5);

	testSuite->assert(bloque->obtenerPosicionX() == 3 && bloque->obtenerPosicionY() == 5,"El Ladrillo se creo correctamente");

	delete bloque;
}
