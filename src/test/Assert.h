#ifndef SRC_TEST_ASSERT_H_
#define SRC_TEST_ASSERT_H_

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


#endif /* SRC_TEST_ASSERT_H_ */
