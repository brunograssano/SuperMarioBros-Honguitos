#ifndef SRC_LECTOR_PARSERLOG_HPP_
#define SRC_LECTOR_PARSERLOG_HPP_

#include "Parser.hpp"

class ParserLog : public Parser{
	public:
        void parsear(pugi::xml_node log, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido)override{};
};




#endif /* SRC_LECTOR_PARSERLOG_HPP_ */
