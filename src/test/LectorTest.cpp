using namespace std;
#include "LectorTest.h"
#include "../lector/Lector.hpp"
#include <iostream>

void LectorTest::ejecutar(Assert* testSuite){

	cout << "========== Comenzando con las pruebas del Lector ==========" << endl;
	test01CuandoLePedisAlLectorQueLeaTraeElAncho(testSuite);
	cout << "========== Finalizando con las pruebas del Lector ==========" << endl;

}

void LectorTest::test01CuandoLePedisAlLectorQueLeaTraeElAncho(Assert* testSuite){

	Lector* lector = new Lector();

	string archivoALeer = "resources/modeloXML.xml";

	ArchivoLeido* archivoLeido = lector->leerArchivo(archivoALeer);

	int anchoEsperado = archivoLeido->anchoVentana;

	testSuite->assert(anchoEsperado,800,"El ancho es de 800 px");

	delete lector;
	delete archivoLeido;
}


