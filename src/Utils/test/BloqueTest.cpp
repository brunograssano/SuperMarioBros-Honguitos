#include "src/Server/modelo/Bloques/Ladrillo.hpp"
#include "src/Server/modelo/Bloques/Sorpresa.hpp"
#include "src/Server/modelo/Bloques/Plataforma.hpp"
#include "BloqueTest.hpp"

#define CYAN "\u001b[36m"
#define AZUL_CLARO "\e[1;34m"
#define RESET "\x1b[0m"

void BloqueTest::ejecutar(Assert* testSuite){

	cout << CYAN"========== Comenzando con las pruebas de bloque ==========" RESET << endl;
    cout << AZUL_CLARO"----------TEST 01----------" RESET << endl;
	test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(testSuite);
    cout << AZUL_CLARO"----------TEST 02----------" RESET<< endl;
	test02SeAniadeUnBloqueAUnaPlataforma(testSuite);

	cout << CYAN"========== Finalizando con las pruebas de bloque ==========" RESET << endl;
}

void BloqueTest::test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite){

	Bloque* bloque = new Ladrillo(3, 5,0);

	testSuite->assert(bloque->obtenerPosicionX() == 0 && bloque->obtenerPosicionY() == 0,"El Ladrillo se posiciono correctamente");

	delete bloque;
}

void BloqueTest::test02SeAniadeUnBloqueAUnaPlataforma(Assert* testSuite){

	auto* plataforma = new Plataforma();
	Bloque* bloque = new Ladrillo(3,5,0);
	plataforma->agregarBloque(bloque);

	int cantidadDeBloques = plataforma->obtenerBloques().size();
	Bloque* bloqueObtenido = plataforma->obtenerBloques().back();

	testSuite->assert(cantidadDeBloques, 1, "Si agregamos un bloque a una plataforma, la cantidad es correcta");
	testSuite->assert(bloqueObtenido == bloque, "El bloque enviado es el mismo que el obtenido");

	delete plataforma;

}
