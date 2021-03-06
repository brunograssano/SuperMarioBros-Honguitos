#ifndef SRC_SERVER_ENVIADORESSERVER_ENVIADORCANTIDADCONEXION_HPP_
#define SRC_SERVER_ENVIADORESSERVER_ENVIADORCANTIDADCONEXION_HPP_

#include "../../Utils/Enviador.hpp"
#include "src/Utils/Utils.hpp"

class EnviadorCantidadConexion :public Enviador {

	public:
		explicit EnviadorCantidadConexion(Socket* socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		actualizacion_cantidad_jugadores_t actualizacion{};

};


#endif /* SRC_SERVER_ENVIADORESSERVER_ENVIADORCANTIDADCONEXION_HPP_ */
