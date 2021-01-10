#ifndef SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORCREDENCIALES_HPP_
#define SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORCREDENCIALES_HPP_

#include "../../Utils/Enviador.hpp"

class EnviadorCredenciales:public Enviador{
	public:
		explicit EnviadorCredenciales(int socket);
		void enviar()override;
		void dejarInformacion(void* informacion)override;

	private:
		credencial_t credenciales;
};


#endif /* SRC_CLIENT_ENVIADORESCLIENTE_ENVIADORCREDENCIALES_HPP_ */
