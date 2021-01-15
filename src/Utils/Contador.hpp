#ifndef SRC_SERVER_CONTADOR_HPP_
#define SRC_SERVER_CONTADOR_HPP_

#include <ctime>

/* No tocar */
#define SEGUNDOS  1				// segundos
#define MSEGUNDOS 1000			// milisegundos
#define USEGUNDOS 1000000		// microsegundos

class Contador{

	public:
		Contador(int tiempo, int unidad){
			tiempoTotal = tiempo;
			tiempoInicio = time(nullptr);
			this->unidad = unidad;
		}

		void iniciar(){
			tiempoInicio = time(nullptr);
		}

		int tiempoRestante() const{
			time_t tiempoActual = time(nullptr);
			double tiempoDesdeElComienzoEnSegundos = difftime(tiempoActual, tiempoInicio);
			int tiempoDesdeElComienzo = (int) tiempoDesdeElComienzoEnSegundos*unidad;
			if(tiempoDesdeElComienzo >= tiempoTotal){
				return 0;
			}else{
				return (tiempoTotal - tiempoDesdeElComienzo);
			}
		}
		~Contador()= default;

	private:
		int tiempoTotal;
		time_t tiempoInicio;
		int unidad;
};



#endif /* SRC_SERVER_CONTADOR_HPP_ */
