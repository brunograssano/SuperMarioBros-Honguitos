#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORINFOPARTIDA_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORINFOPARTIDA_HPP_

#include "../../Utils/Enviador.hpp"

class EnviadorInfoPartida:public Enviador{
	public:
		explicit EnviadorInfoPartida(Socket* socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;
	private:
		info_partida_t info_comienzo_partida{};
};


#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORINFOPARTIDA_HPP_ */
