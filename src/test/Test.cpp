using namespace std;
#include <iostream>
#include <string>
#include <stdio.h>

#include "BloqueTest.h"
#include "MarioTest.h"
#include "LectorTest.h"
#include "Assert.h"


int main(int argc, char* argv[]){
	Assert* testSuite = new Assert();
/*
	MarioTest* marioTest = new MarioTest();
	marioTest->ejecutar(testSuite);
	delete marioTest;

	BloqueTest* bloqueTest = new BloqueTest();
	bloqueTest->ejecutar(testSuite);
	delete bloqueTest;
*/
	LectorTest* lectorTest = new LectorTest();
	lectorTest->ejecutar(testSuite);
	delete lectorTest;

	cout << "Pasaron " << testSuite->getPruebasPasadas() << " pruebas de "<< testSuite->getPruebasTotales() << endl;
	delete testSuite;
	return 0;
}

