
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
#include "PodioTest.hpp"
#include "TuberiaTest.hpp"


int mainTest(){
	auto testSuite = Assert();

	MarioTest::ejecutar(&testSuite);
	BloqueTest::ejecutar(&testSuite);
	LectorTest::ejecutar(&testSuite);
	EnemigoTest::ejecutar(&testSuite);
	ColisionadorTest::ejecutar(&testSuite);
	MonedaTest::ejecutar(&testSuite);
	PisoTest::ejecutar(&testSuite);
    PodioTest::ejecutar(&testSuite);
    TuberiaTest::ejecutar(&testSuite);

    std::cout << "Pasaron " << testSuite.getPruebasPasadas() << " pruebas de "<< testSuite.getPruebasTotales() << std::endl;

	return 0;
}

