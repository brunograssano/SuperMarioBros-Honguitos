#include "BloqueTest.hpp"

void BloqueTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas de bloque ==========" << endl;

	test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(testSuite);
	test02SeAniadeUnBloqueAUnaPlataforma(testSuite);

	cout << "========== Finalizando con las pruebas de bloque ==========" << endl;
}

void BloqueTest::test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite){

	Bloque* bloque = new Ladrillo(3, 5,0);

	testSuite->assert(bloque->obtenerPosicionX() == 0 && bloque->obtenerPosicionY() == 0,"El Ladrillo se posiciono correctamente");

	delete bloque;
}

void BloqueTest::test02SeAniadeUnBloqueAUnaPlataforma(Assert* testSuite){

	Plataforma* plataforma = new Plataforma();
	Bloque* bloque = new Ladrillo(3,5,0);
	plataforma->agregarBloque(bloque);

	int cantidadDeBloques = plataforma->obtenerBloques().size();
	Bloque* bloqueObtenido = plataforma->obtenerBloques().back();

	testSuite->assert(cantidadDeBloques, 1, "Si agregamos un bloque a una plataforma, la cantidad es correcta");
	testSuite->assert(bloqueObtenido == bloque, "El bloque enviado es el mismo que el obtenido");

	delete plataforma;

}
