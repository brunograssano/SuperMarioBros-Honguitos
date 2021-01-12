#include "src/Server/modelo/Bloques/Ladrillo.hpp"
#include "src/Server/modelo/Bloques/Sorpresa.hpp"
#include "BloqueTest.hpp"

#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

void BloqueTest::ejecutar(Assert* testSuite){

	cout << CYAN"========== Comenzando con las pruebas de bloque ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
	test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(testSuite);

	cout << CYAN"========== Finalizando con las pruebas de bloque ==========" RESET << endl;
}

void BloqueTest::test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite){

	Bloque* bloque = new Ladrillo(3, 5,0);

	testSuite->assert(bloque->obtenerPosicionX() == 0 && bloque->obtenerPosicionY() == 0,"El Ladrillo se posiciono correctamente");

	delete bloque;
}