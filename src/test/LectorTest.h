#ifndef SRC_TEST_LECTORTEST_H_
#define SRC_TEST_LECTORTEST_H_

using namespace std;
#include <iostream>
#include <string>

#include <stdio.h>

#include "../lector/Lector.hpp"
#include "Assert.h"
class LectorTest{

	public:
		void ejecutar(Assert* testSuite);
		void test01CuandoLePedisAlLectorQueLeaTraeElAncho(Assert* testSuite);

};





#endif /* SRC_TEST_LECTORTEST_H_ */
