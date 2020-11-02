#include "ParserLog.hpp"


void ParserLog::ParsearLog(pugi::xml_node log,ArchivoLeido* archivoLeido){
	string level = log.child_value("level");
	if(level.compare("ERROR") == 0){
		archivoLeido->tipoLog = new Error();
	}else if(level.compare("DEBUG") == 0){
		archivoLeido->tipoLog = new Debug();
	}else if(level.compare("INFO") == 0){
		archivoLeido->tipoLog = new Info();
	}else{
		if(level.compare("")==0){
			archivoLeido->mensajeError.push_back("No se ingreso un nivel de log, se carga el por defecto (ERROR)");
		}
		else{
			archivoLeido->mensajeError.push_back("El tipo de log ("+level+") ingresado es incorrecto, se carga el por defecto (ERROR)");
		}
		archivoLeido->tipoLog = new Error();
	}
}

