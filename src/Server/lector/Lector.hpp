#ifndef SRC_SERVER_LECTOR_LECTOR_HPP_
#define SRC_SERVER_LECTOR_LECTOR_HPP_

using namespace std;
#include <string>
#include "ArchivoLeido.hpp"

class Lector{
	public:
		static ArchivoLeido leerArchivo(const string& nombreArchivo);
};




#endif /* SRC_SERVER_LECTOR_LECTOR_HPP_ */
