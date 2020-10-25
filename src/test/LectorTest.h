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
		void test02CuandoLePedisAlLectorQueLeaTraeElAlto(Assert* testSuite);
		void test03CuandoLePedisAlLectorElArchivoSeLeeCorrectamente(Assert* testSuite);
		void test04CuandoLePedisAlLectorElArchivoSeLeeCorrectamenteNoTraeMensajesDeError(Assert* testSuite);
		void test05CuandoLeEnviasUnArchivoQueNoExisteSeLanzaUnError(Assert* testSuite);
		void test06CuandoLeEnviasUnArchivoMalFormateadoSeLanzaUnError(Assert* testSuite);
		void test07CuandoLeEnviasUnArchivoMalElAnchoSeCargaElDefaultYSeLanzaUnError(Assert* testSuite);
		void test08CuandoLeEnviasUnArchivoMalElAltooSeCargaElDefaultYSeLanzaUnError(Assert* testSuite);
};





#endif /* SRC_TEST_LECTORTEST_H_ */
