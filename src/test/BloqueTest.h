#ifndef SRC_TEST_BLOQUETEST_H_
#define SRC_TEST_BLOQUETEST_H_
using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "../modelo/bloques/Bloque.h"
#include "Assert.h"


class BloqueTest{

	public:
		void ejecutar(Assert* testSuite );
		void test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite);
		void test02SeAniadeUnBloqueAUnaPlataforma(Assert* testSuite);
};

#endif /* SRC_TEST_BLOQUETEST_H_ */
