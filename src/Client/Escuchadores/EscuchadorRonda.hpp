#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_


class Cliente;
#include "../Cliente.hpp"

#include "../app/juegoCliente/RecorteBloque.hpp"
#include "../app/juegoCliente/RecorteMoneda.hpp"
#include "../app/juegoCliente/RecorteGoomba.hpp"
#include "../app/juegoCliente/RecorteKoopa.hpp"

#include "../../Utils/Escuchador.hpp"

class EscuchadorRonda: public Escuchador{

	public:
		EscuchadorRonda(int socketCliente, Cliente* cliente);
		virtual ~EscuchadorRonda();
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

		bool bloquesValidos(bloque_t bloques[MAX_BLOQUES], int tope);
		bool monedasValidas(moneda_t monedas[MAX_MONEDAS], int tope);
		bool enemigosValidos(enemigo_t enemigos[MAX_ENEMIGOS], int tope);

		bool recibioMensajeValido();
	private:
		Cliente* cliente;
		info_ronda_t info_ronda;
		string error;
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_ */
