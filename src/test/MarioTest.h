#ifndef SRC_TEST_MARIOTEST_H_
#define SRC_TEST_MARIOTEST_H_
using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "../modelo/Mario.h"
#include "Assert.h"
class MarioTest{

	public:
		void ejecutar(Assert* testSuite);
		void test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(Assert* testSuite);
		void test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(Assert* testSuite);
		void test03MarioEmpiezaConCeroMonedas(Assert* testSuite);
		void test04MarioEmpiezaConCeroPuntos(Assert* testSuite);
		void test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(Assert* testSuite);
};


#endif /* SRC_TEST_MARIOTEST_H_ */
