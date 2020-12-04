#ifndef SRC_SERVER_CONTADOR_HPP_
#define SRC_SERVER_CONTADOR_HPP_

#include <time.h>
class Contador{

	public:
		Contador(int tiempo/*En micro segundos*/){
			tiempoTotal = tiempo;
			tiempoInicio = time(nullptr);
		}
		/*En microsegundos*/
		int tiempoRestante(){
			time_t tiempoActual = time(nullptr);
			double tiempoDesdeElComienzoEnSegundos = difftime(tiempoInicio, tiempoActual);
			int tiempoDesdeElComienzoEnMicroSegundos = (int) tiempoDesdeElComienzoEnSegundos*1000000; //s*e6/e6 = us*e6
			if(tiempoDesdeElComienzoEnMicroSegundos >= tiempoTotal){
				return 0;
			}else{
				return (tiempoTotal - tiempoDesdeElComienzoEnMicroSegundos);
			}
		}
		~Contador(){
		}

	private:
		int tiempoTotal;
		time_t tiempoInicio;
};



#endif /* SRC_SERVER_CONTADOR_HPP_ */
