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
		static void ejecutar(Assert* testSuite);
		static void test01CuandoPedisAMarioQueSeMuevaADerechaSeMueve(Assert* testSuite);
		static void test02CuandoPedisAMarioQueSeMuevaAIzquierdaSeMueve(Assert* testSuite);
		static void test03AgregarMonedasAMarioSumaCincuentaPuntos(Assert* testSuite);
		static void test04MarioEmpiezaConCeroPuntos(Assert* testSuite);
		static void test05MarioGanaDiezPuntosYDevuelveEsoDeTotal(Assert* testSuite);
        static void test06MarioEmpiezaCon3VidasYLasPierdedependiendoElCaso(Assert* testSuite);
};


#endif /* SRC_UTILS_TEST_MARIOTEST_HPP_ */
