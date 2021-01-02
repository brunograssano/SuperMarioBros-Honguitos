#ifndef SRC_LECTOR_PARSERNIVEL_HPP_
#define SRC_LECTOR_PARSERNIVEL_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "ParserEnemigo.hpp"
#include "ParserPlataforma.hpp"

class ParserNivel{
	public:
			static void ParsearNivel(pugi::xml_node nivel,ArchivoLeido* archivoLeido);
};


#endif /* SRC_LECTOR_PARSERNIVEL_HPP_ */
