#ifndef SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_

#include <string>

class OcultadorDeTexto{
	public:
		virtual ~OcultadorDeTexto()= default;
		virtual std::string ocultar(std::string texto)=0;
};

class OcultadorDeTextoAstericos: public OcultadorDeTexto{
	public:
		OcultadorDeTextoAstericos()= default;
        std::string ocultar(std::string texto)override;
		~OcultadorDeTextoAstericos() override= default;
};

class OcultadorDeTextoNulo: public OcultadorDeTexto{
	public:
		OcultadorDeTextoNulo()= default;
        std::string ocultar(std::string texto)override;
		~OcultadorDeTextoNulo() override= default;
};

#endif /* SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_ */
