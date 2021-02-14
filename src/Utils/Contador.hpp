#ifndef SRC_SERVER_CONTADOR_HPP_
#define SRC_SERVER_CONTADOR_HPP_

#include <ctime>

/* No tocar */
#define SEGUNDOS  1				// segundos
#define MSEGUNDOS 1000			// milisegundos
#define USEGUNDOS 1000000		// microsegundos

class Contador{

	public:
		Contador(int tiempo, int unidad);
		void iniciar();
		int tiempoRestante() const;
		~Contador()= default;

	private:
		int tiempoTotal;
		time_t tiempoInicio;
		int unidad;
};



#endif /* SRC_SERVER_CONTADOR_HPP_ */
