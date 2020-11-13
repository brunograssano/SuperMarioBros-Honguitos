#ifndef SRC_LECTOR_PARSERS_PARSERUSUARIO_HPP_
#define SRC_LECTOR_PARSERS_PARSERUSUARIO_HPP_

#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"

class ParserUsuario{
	public:
		void parsearUsuario(pugi::xml_node usuario,ArchivoLeido* archivoLeido);
};


#endif /* SRC_LECTOR_PARSERS_PARSERUSUARIO_HPP_ */
