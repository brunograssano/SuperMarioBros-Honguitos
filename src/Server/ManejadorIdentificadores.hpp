#ifndef SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_
#define SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_

#include <vector>
using namespace std;

class ManejadorIdentificadores{

	public:
		ManejadorIdentificadores();
		~ManejadorIdentificadores();
		int obtenerIDNueva();

    private:
		vector<int> mapaID;
		int cantidadIDs;

};



#endif /* SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_ */
