#ifndef SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_
#define SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_

using namespace std;

#include <vector>

class ManejadorIdentificadores{


	public:
		ManejadorIdentificadores();
		~ManejadorIdentificadores();

		int obtenerIDNueva();
		vector<int> obtenerTodasLasID();

	private:
		vector<int> mapaID;
		int cantidadIDs;

};



#endif /* SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_ */
