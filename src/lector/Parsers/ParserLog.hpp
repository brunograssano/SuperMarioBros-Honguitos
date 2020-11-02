#ifndef SRC_LECTOR_PARSERLOG_HPP_
#define SRC_LECTOR_PARSERLOG_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "../../log/Error.hpp"
#include "../../log/Debug.hpp"
#include "../../log/Info.hpp"

class ParserLog{
	public:
			void ParsearLog(pugi::xml_node log,ArchivoLeido* archivoLeido);
};




#endif /* SRC_LECTOR_PARSERLOG_HPP_ */
