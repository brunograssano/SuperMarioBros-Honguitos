#ifndef SRC_LECTOR_PARSERLOG_HPP_
#define SRC_LECTOR_PARSERLOG_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "../../../Utils/log/Error.hpp"
#include "../../../Utils/log/Debug.hpp"
#include "../../../Utils/log/Info.hpp"
#include "Parser.h"

class ParserLog : public Parser{
	public:
        void parsear(pugi::xml_node log, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido)override{};
};




#endif /* SRC_LECTOR_PARSERLOG_HPP_ */
