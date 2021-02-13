#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORACTUALIZACIONJUGADORES_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORACTUALIZACIONJUGADORES_HPP_

#include "src/Utils/Socket.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Utils/Utils.hpp"
class Cliente;
#include "src/Client/Cliente.hpp"

class EscuchadorActualizacionJugadores: public Escuchador{

	public:
		EscuchadorActualizacionJugadores(Socket* socketCliente, Cliente* cliente);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

		static bool idsValidas(par_id_nombre_t pares_id_nombre[MAX_JUGADORES], int tope);
		bool recibioMensajeValido();

	private:
		actualizacion_cantidad_jugadores_t actualizacion{};
		Cliente* cliente;
        std::string error;
};

#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORACTUALIZACIONJUGADORES_HPP_ */
