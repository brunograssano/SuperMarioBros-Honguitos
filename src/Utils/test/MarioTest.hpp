#ifndef SRC_UTILS_TEST_MARIOTEST_HPP_
#define SRC_UTILS_TEST_MARIOTEST_HPP_

using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "src/Server/modelo/Mario/Mario.hpp"
#include "Assert.hpp"
class MarioTest{

	public:
		void ejecutar(Assert* testSuite);
		void test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(Assert* testSuite);
		void test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(Assert* testSuite);
		void test03MarioEmpiezaConCeroMonedas(Assert* testSuite);
		void test04MarioEmpiezaConCeroPuntos(Assert* testSuite);
		void test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(Assert* testSuite);
};


#endif /* SRC_UTILS_TEST_MARIOTEST_HPP_ */
