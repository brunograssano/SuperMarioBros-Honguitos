#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_

#include <string>
#include <queue>
using namespace std;

#include "../../Utils/Enviador.hpp"


class EnviadorMensajeLog:public Enviador{

	public:
		EnviadorMensajeLog(int socket);
		~EnviadorMensajeLog(){};
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		queue<mensaje_log_t> mensajesLog;


};



#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORMENSAJELOG_HPP_ */
