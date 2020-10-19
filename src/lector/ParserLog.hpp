#ifndef SRC_LECTOR_PARSERLOG_HPP_
#define SRC_LECTOR_PARSERLOG_HPP_
using namespace std;
#include <string>
#include "pugixml.hpp"
#include "ArchivoLeido.hpp"
#include "../log/Error.h"
#include "../log/Debug.h"
#include "../log/Info.h"

class ParserLog{
	public:
			void ParsearLog(pugi::xml_node log,ArchivoLeido* archivoLeido){
				string level = log.child_value("level");
				if(level.compare("ERROR") == 0){
					archivoLeido->tipoLog = new Error();
				}else if(level.compare("DEBUG") == 0){
					archivoLeido->tipoLog = new Debug();
				}else if(level.compare("INFO") == 0){
					archivoLeido->tipoLog = new Info();
				}
			 }
};




#endif /* SRC_LECTOR_PARSERLOG_HPP_ */
