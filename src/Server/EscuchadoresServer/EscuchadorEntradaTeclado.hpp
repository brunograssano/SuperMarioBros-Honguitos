#ifndef SERVER_ESCUCHADORENTRADATECLADO_HPP_
#define SERVER_ESCUCHADORENTRADATECLADO_HPP_


#include "src/Utils/Socket.hpp"
#include "src/Server/Servidor/Servidor.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Utils/Utils.hpp"

class EscuchadorEntradaTeclado: public Escuchador{

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
