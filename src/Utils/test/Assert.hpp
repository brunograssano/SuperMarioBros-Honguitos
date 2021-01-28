#ifndef SRC_UTILS_TEST_ASSERT_HPP_
#define SRC_UTILS_TEST_ASSERT_HPP_

#include <iostream>
#include <string>
#include <cstdio>

class Assert{
	public:
		void assert(int obtenido, int esperado, const std::string& textoExplicativo);
		void assert(float obtenido, float esperado, float delta, const std::string& textoExplicativo);
		void assert(bool condicion, const std::string& textoExplicativo);
		void assert(const std::string& obtenido, const std::string& esperado, const std::string& textoExplicativo);
		int getPruebasPasadas() const;
		int getPruebasTotales() const;

	private:
		int pruebasPasadas = 0;
		int pruebasTotales = 0;
};


#endif /* SRC_UTILS_TEST_ASSERT_HPP_ */
