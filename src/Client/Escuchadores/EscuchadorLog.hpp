#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORLOG_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORLOG_HPP_

#include <string>
#include "src/Utils/Utils.hpp"
#include "src/Utils/log/Log.hpp"
#include "src/Utils/Escuchador.hpp"

class EscuchadorLog : public Escuchador{

	public:

		explicit EscuchadorLog(Socket* socket);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
		mensaje_log_t conjuntoMensajeLog{};
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORLOG_HPP_ */
