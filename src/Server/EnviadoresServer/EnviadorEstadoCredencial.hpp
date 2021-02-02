#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORESTADOCREDENCIAL_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORESTADOCREDENCIAL_HPP_

#include "../../Utils/Enviador.hpp"

class EnviadorEstadoCredencial:public Enviador{
	public:
		explicit EnviadorEstadoCredencial(Socket* socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		verificacion_t estadoCredencial;
};



#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORESTADOCREDENCIAL_HPP_ */
