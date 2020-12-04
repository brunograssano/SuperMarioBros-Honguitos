#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORRONDA_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORRONDA_HPP_

#include <queue>

#include "../../Utils/Enviador.hpp"


class EnviadorRonda:public Enviador{
	public:
		EnviadorRonda(int socket);
		~EnviadorRonda(){};
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		queue<info_ronda_t> colaRondas;

};

#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORRONDA_HPP_ */
