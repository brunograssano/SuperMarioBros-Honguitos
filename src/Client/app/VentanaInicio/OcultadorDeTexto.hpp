#ifndef SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_

#include <string>
using namespace std;


class OcultadorDeTexto{
	public:
		virtual ~OcultadorDeTexto(){};
		virtual string ocultar(string texto){return string("");};
};

class OcultadorDeTextoAstericos: public OcultadorDeTexto{

	public:
		OcultadorDeTextoAstericos(){}
		string ocultar(string texto)override{
			return string(texto.length(), '*');
		}
		~OcultadorDeTextoAstericos(){}
};

class OcultadorDeTextoNulo: public OcultadorDeTexto{
	public:
		OcultadorDeTextoNulo(){}
		string ocultar(string texto)override{
			return texto;
		}
		~OcultadorDeTextoNulo(){}
};

#endif /* SRC_CLIENT_APP_VENTANAINICIO_OCULTADORDETEXTO_HPP_ */
