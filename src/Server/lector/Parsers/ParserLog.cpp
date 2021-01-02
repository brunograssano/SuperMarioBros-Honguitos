#include "ParserLog.hpp"


void ParserLog::ParsearLog(pugi::xml_node log,ArchivoLeido* archivoLeido){
	string level = log.child_value("level");
	if(level == "ERROR"){
		archivoLeido->tipoLog = new Error();
	}else if(level == "DEBUG"){
		archivoLeido->tipoLog = new Debug();
	}else if(level == "INFO"){
		archivoLeido->tipoLog = new Info();
	}else{
		if(level.empty()){
			archivoLeido->mensajeError.emplace_back("No se ingreso un nivel de log, se carga el por defecto (ERROR)");
		}
		else{
			archivoLeido->mensajeError.push_back("El tipo de log ("+level+") ingresado es incorrecto, se carga el por defecto (ERROR)");
		}
		archivoLeido->tipoLog = new Error();
	}
}

