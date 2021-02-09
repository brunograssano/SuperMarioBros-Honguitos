#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORRONDA_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORRONDA_HPP_

#include "../../Utils/ColaBloqueante.hpp"
#include "../../Utils/Enviador.hpp"

class EnviadorRonda:public Enviador{
	public:
		explicit EnviadorRonda(Socket* socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
        BlockingQueue<info_ronda_t> colaRondas;

};

#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORRONDA_HPP_ */