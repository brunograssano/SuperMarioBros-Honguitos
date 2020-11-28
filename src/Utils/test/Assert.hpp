#ifndef SRC_UTILS_TEST_ASSERT_HPP_
#define SRC_UTILS_TEST_ASSERT_HPP_

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

class Assert{
	public:

		void assert(int obtenido, int esperado, string textoExplicativo){
			cout << textoExplicativo << ": ";
			if(obtenido==esperado){
				cout << "todo bien" <<endl;
				pruebasPasadas++;
			}
			else{
				cout << "todo mal" <<endl;
			}
			pruebasTotales++;
		}
		void assert(float obtenido, float esperado, float delta, string textoExplicativo){
			cout << textoExplicativo << ": ";
			if(obtenido < esperado + delta && obtenido > esperado - delta){
				cout << "todo bien" <<endl;
				pruebasPasadas++;
			}
			else{
				cout << "todo mal" <<endl;
			}
			pruebasTotales++;
		}

		void assert(bool condicion, string textoExplicativo){
			cout << textoExplicativo << ": ";
			if(condicion){
				cout << "todo bien" <<endl;
				pruebasPasadas++;
			}
			else{
				cout << "todo mal" <<endl;
			}
			pruebasTotales++;
		}

		void assert(string obtenido, string esperado, string textoExplicativo){
			cout << textoExplicativo << ": ";
			if(obtenido.compare(esperado) == 0){
				cout << "todo bien" <<endl;
				pruebasPasadas++;
			}
			else{
				cout << "todo mal" <<endl;
			}
			pruebasTotales++;
		}

		int getPruebasPasadas(){
			return pruebasPasadas;
		}
		int getPruebasTotales(){
			return pruebasTotales;
		}

	private:
		int pruebasPasadas = 0;
		int pruebasTotales = 0;
};


#endif /* SRC_UTILS_TEST_ASSERT_HPP_ */