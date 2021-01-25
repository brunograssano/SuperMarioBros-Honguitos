#ifndef SRC_UTILS_TEST_BLOQUETEST_HPP_
#define SRC_UTILS_TEST_BLOQUETEST_HPP_

#include <iostream>
#include <string>
using namespace std;

#include "../../Server/Modelo/Juego/Nivel/Bloques/Bloque.hpp"
#include "Assert.hpp"


class BloqueTest{

	public:
		static void ejecutar(Assert* testSuite );
		static void test01ElBloqueDeLadrilloSeCreaConUnaPosicionCorrecta(Assert* testSuite);

};

#endif /* SRC_UTILS_TEST_BLOQUETEST_HPP_ */
