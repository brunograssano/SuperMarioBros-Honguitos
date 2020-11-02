#ifndef SRC_LECTOR_PARSERVENTANA_HPP_
#define SRC_LECTOR_PARSERVENTANA_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"

class ParserVentana{
	public:
			void ParsearVentana(pugi::xml_node ventana,ArchivoLeido* archivoLeido);
};

#endif /* SRC_LECTOR_PARSERVENTANA_HPP_ */
