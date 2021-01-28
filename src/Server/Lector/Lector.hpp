#ifndef SRC_SERVER_LECTOR_LECTOR_HPP_
#define SRC_SERVER_LECTOR_LECTOR_HPP_

#include <string>
#include "ArchivoLeido.hpp"

class Lector{
	public:
		static ArchivoLeido leerArchivo(const std::string& nombreArchivo);
};




#endif /* SRC_SERVER_LECTOR_LECTOR_HPP_ */
