
using namespace std;
#include <iostream>
#include <string>

#include "BloqueTest.hpp"
#include "MarioTest.hpp"
#include "LectorTest.hpp"
#include "Assert.hpp"


int mainTest(){
	auto* testSuite = new Assert();
	/*
	MarioTest* marioTest = new MarioTest();
	marioTest->ejecutar(testSuite);
	delete marioTest;
    */
	BloqueTest* bloqueTest = new BloqueTest();
	bloqueTest->ejecutar(testSuite);
	delete bloqueTest;

	LectorTest::ejecutar(testSuite);

	cout << "Pasaron " << testSuite->getPruebasPasadas() << " pruebas de "<< testSuite->getPruebasTotales() << endl;
	delete testSuite;
	return 0;
}

