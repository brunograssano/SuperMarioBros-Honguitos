#ifndef SERVER_ESCUCHADORENTRADATECLADO_HPP_
#define SERVER_ESCUCHADORENTRADATECLADO_HPP_

#include "src/Server/Servidor/Servidor.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Escuchador.hpp"

class EscuchadorEntradaTeclado:public Escuchador{

	public:
		EscuchadorEntradaTeclado(Socket* socket, int idJugador, Servidor* servidor);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
		entrada_usuario_t entradaUsuario{};
		int idJugador;
		Servidor* servidor;

};

#endif /* SERVER_ESCUCHADORENTRADATECLADO_HPP_ */
