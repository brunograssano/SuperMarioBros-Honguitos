#ifndef SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_

#include <string>
using namespace std;


class OcultadorDeTexto{
	public:
		virtual ~OcultadorDeTexto()= default;
		virtual string ocultar(string texto){return string("");};
};

class OcultadorDeTextoAstericos: public OcultadorDeTexto{

	public:
		OcultadorDeTextoAstericos()= default;
		string ocultar(string texto)override{
			return string(texto.length(), '*');
		}
		~OcultadorDeTextoAstericos() override= default;
};

class OcultadorDeTextoNulo: public OcultadorDeTexto{
	public:
		OcultadorDeTextoNulo()= default;
		string ocultar(string texto)override{
			return texto;
		}
		~OcultadorDeTextoNulo() override= default;
};

#endif /* SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_ */
