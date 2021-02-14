#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_

#include "../../Utils/Enviador.hpp"
#include "../../Utils/ColaBloqueante.hpp"
#include "src/Utils/Utils.hpp"

class EnviadorMensajeLog:public Enviador{

	public:
		explicit EnviadorMensajeLog(Socket* socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
        BlockingQueue<mensaje_log_t> mensajesLog;
};


#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_ */