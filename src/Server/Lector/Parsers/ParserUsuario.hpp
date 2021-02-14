#ifndef SRC_SERVER_LECTOR_PARSERS_PARSERUSUARIO_HPP_
#define SRC_SERVER_LECTOR_PARSERS_PARSERUSUARIO_HPP_

#include "Parser.hpp"

class ParserUsuario : public Parser{
	public:
		void parsear(pugi::xml_node usuario, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido)override{};
};


#endif /* SRC_SERVER_LECTOR_PARSERS_PARSERUSUARIO_HPP_ */
