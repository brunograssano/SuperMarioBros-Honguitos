#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_


class Cliente;
#include "../Cliente.hpp"
#include "../../Utils/Escuchador.hpp"

class EscuchadorRonda: public Escuchador{

	public:
		EscuchadorRonda(int socketCliente, Cliente* cliente);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
        static bool bloquesValidos(entidad_t bloques[MAX_SORPRESAS], int tope);
        static bool monedasValidas(entidad_t monedas[MAX_MONEDAS], int tope);
        static bool enemigosValidos(entidad_t enemigos[MAX_ENEMIGOS], int tope);

        bool recibioMensajeValido();
		Cliente* cliente;
		info_ronda_t info_ronda{};
        std::string error;
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_ */
