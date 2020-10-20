#ifndef SRC_LECTOR_PARSERPLATAFORMA_HPP_
#define SRC_LECTOR_PARSERPLATAFORMA_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"

class ParserPlataforma{
	public:
			void ParsearPlataforma(pugi::xml_node plataforma,Nivel* unNivel);
};




#endif /* SRC_LECTOR_PARSERPLATAFORMA_HPP_ */
