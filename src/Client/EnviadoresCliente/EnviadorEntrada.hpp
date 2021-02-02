#ifndef SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORENTRADA_HPP_
#define SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORENTRADA_HPP_

#include <queue>

#include "src/Utils/Enviador.hpp"

class EnviadorEntrada:public Enviador{
	public:
		explicit EnviadorEntrada(Socket* socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
        std::queue<entrada_usuario_t> entradasUsuario;
};


#endif /* SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORENTRADA_HPP_ */
