
using namespace std;
#include <iostream>
#include <string>

#include "BloqueTest.hpp"
#include "MarioTest.hpp"
#include "LectorTest.hpp"
#include "EnemigoTest.hpp"
#include "ColisionadorTest.hpp"
#include "MonedaTest.hpp"
#include "PisoTest.hpp"
#include "Assert.hpp"
#include "PisoTest.hpp"


int mainTest(){
	auto testSuite = Assert();

	MarioTest::ejecutar(&testSuite);
	BloqueTest::ejecutar(&testSuite);
	LectorTest::ejecutar(&testSuite);
	EnemigoTest::ejecutar(&testSuite);
	ColisionadorTest::ejecutar(&testSuite);
	MonedaTest::ejecutar(&testSuite);
	PisoTest::ejecutar(&testSuite);

	cout << "Pasaron " << testSuite.getPruebasPasadas() << " pruebas de "<< testSuite.getPruebasTotales() << endl;
	return 0;
}

