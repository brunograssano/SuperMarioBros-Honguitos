#ifndef SRC_TEST_BLOQUETEST_HPP_
#define SRC_TEST_BLOQUETEST_HPP_

using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "../modelo/Bloques/Bloque.hpp"
#include "Assert.hpp"


class BloqueTest{

	public:
		void ejecutar(Assert* testSuite );
		void test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite);
		void test02SeAniadeUnBloqueAUnaPlataforma(Assert* testSuite);
};

#endif /* SRC_TEST_BLOQUETEST_HPP_ */
