#ifndef SRC_SERVER_LECTOR_PARSERS_PARSERUSUARIO_HPP_
#define SRC_SERVER_LECTOR_PARSERS_PARSERUSUARIO_HPP_

#include "../ArchivoLeido.hpp"
#include "../pugixml.hpp"

class ParserUsuario{
	public:
		void parsearUsuario(pugi::xml_node usuario,ArchivoLeido* archivoLeido);
};


#endif /* SRC_SERVER_LECTOR_PARSERS_PARSERUSUARIO_HPP_ */
