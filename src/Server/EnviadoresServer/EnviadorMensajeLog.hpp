#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_

#include <queue>

#include "../../Utils/Enviador.hpp"


class EnviadorMensajeLog:public Enviador{

	public:
		explicit EnviadorMensajeLog(int socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
        std::queue<mensaje_log_t> mensajesLog;
};


#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_ */