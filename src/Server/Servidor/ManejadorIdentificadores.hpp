#ifndef SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_
#define SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_

#include <vector>

class ManejadorIdentificadores{

	public:
		ManejadorIdentificadores();
		~ManejadorIdentificadores();
		int obtenerIDNueva();

    private:
        std::vector<int> mapaID;
		int cantidadIDs;

};



#endif /* SRC_SERVER_MANEJADORIDENTIFICADORES_HPP_ */
