using namespace std;
#include "LectorTest.h"
#include "../lector/Lector.h"
#include <iostream>

void LectorTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas del Lector ==========" << endl;
	test01CuandoLePedisAlLectorQueLeaTraeElAncho(testSuite);
	cout << "========== Finalizando con las pruebas del Lector ==========" << endl;

}

void LectorTest::test01CuandoLePedisAlLectorQueLeaTraeElAncho(Assert* testSuite){

	Lector* lector = new Lector();

	char* archivoALeer = "modeloXML.xml";

	string ancho = lector->leerArchivo(archivoALeer);

	int anchoEsperado = stoi(ancho);

	testSuite->assert(anchoEsperado,800,"El ancho es de 800 px");

	delete lector;
}


