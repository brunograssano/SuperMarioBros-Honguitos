#ifndef SRC_LECTOR_PARSERLOG_HPP_
#define SRC_LECTOR_PARSERLOG_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "../../../Utils/log/Error.hpp"
#include "../../../Utils/log/Debug.hpp"
#include "../../../Utils/log/Info.hpp"

class ParserLog{
	public:
			void ParsearLog(pugi::xml_node log,ArchivoLeido* archivoLeido);
};




#endif /* SRC_LECTOR_PARSERLOG_HPP_ */
