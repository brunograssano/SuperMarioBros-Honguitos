#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORINFOVENTANAINICIO_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORINFOVENTANAINICIO_HPP_

#include "../../Utils/Enviador.hpp"

class EnviadorInfoVentanaInicio:public Enviador{
	public:
		EnviadorInfoVentanaInicio(int socket);
		~EnviadorInfoVentanaInicio(){};
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		info_inicio_t info_inicio_ventana;
};



#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORINFOVENTANAINICIO_HPP_ */
