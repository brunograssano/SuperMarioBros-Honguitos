#ifndef SRC_UTILS_TEST_ASSERT_HPP_
#define SRC_UTILS_TEST_ASSERT_HPP_

#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

class Assert{
	public:
		void assert(int obtenido, int esperado, const string& textoExplicativo);
		void assert(float obtenido, float esperado, float delta, const string& textoExplicativo);
		void assert(bool condicion, const string& textoExplicativo);
		void assert(const string& obtenido, const string& esperado, const string& textoExplicativo);
		int getPruebasPasadas() const;
		int getPruebasTotales() const;

	private:
		int pruebasPasadas = 0;
		int pruebasTotales = 0;
};


#endif /* SRC_UTILS_TEST_ASSERT_HPP_ */
