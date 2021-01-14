
using namespace std;
#include <iostream>
#include <string>

#include "BloqueTest.hpp"
#include "MarioTest.hpp"
#include "LectorTest.hpp"
#include "EnemigoTest.hpp"
#include "Assert.hpp"
#include "PodioTest.hpp"


int mainTest(){
	auto* testSuite = new Assert();

	MarioTest::ejecutar(testSuite);
	BloqueTest::ejecutar(testSuite);
	LectorTest::ejecutar(testSuite);
	EnemigoTest::ejecutar(testSuite);
    PodioTest::ejecutar(testSuite);
	cout << "Pasaron " << testSuite->getPruebasPasadas() << " pruebas de "<< testSuite->getPruebasTotales() << endl;
	delete testSuite;
	return 0;
}

