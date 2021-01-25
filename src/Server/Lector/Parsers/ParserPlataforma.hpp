#ifndef SRC_LECTOR_PARSERPLATAFORMA_HPP_
#define SRC_LECTOR_PARSERPLATAFORMA_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "Parser.hpp"

class ParserPlataforma : public Parser{
	public:
        void parsear(pugi::xml_node plataforma, Nivel* unNivel, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,ArchivoLeido* archivoLeido) override{};
};




#endif /* SRC_LECTOR_PARSERPLATAFORMA_HPP_ */
