#ifndef SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORENTRADA_HPP_
#define SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORENTRADA_HPP_

#include <queue>

#include "../../Utils/Enviador.hpp"

class EnviadorEntrada:public Enviador{
	public:
		EnviadorEntrada(int socket);
		~EnviadorEntrada(){};
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		queue<entrada_usuario_t> entradasUsuario;
};


#endif /* SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORENTRADA_HPP_ */
