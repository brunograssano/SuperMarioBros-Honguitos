#ifndef SRC_UTILS_TEST_BLOQUETEST_HPP_
#define SRC_UTILS_TEST_BLOQUETEST_HPP_

using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "../../Server/modelo/Bloques/Bloque.hpp"
#include "Assert.hpp"


class BloqueTest{

	public:
		static void ejecutar(Assert* testSuite );
		static void test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite);
		static void test02SeAniadeUnBloqueAUnaPlataforma(Assert* testSuite);
};

#endif /* SRC_UTILS_TEST_BLOQUETEST_HPP_ */
