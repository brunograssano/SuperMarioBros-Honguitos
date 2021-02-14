#ifndef SRC_LECTOR_PARSERVENTANA_HPP_
#define SRC_LECTOR_PARSERVENTANA_HPP_

#include "Parser.hpp"

class ParserVentana : public Parser{
	public:
        void parsear(pugi::xml_node ventana, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido)override{};
};

#endif /* SRC_LECTOR_PARSERVENTANA_HPP_ */
