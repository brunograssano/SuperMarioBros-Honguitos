#include "ParserPlataforma.hpp"

#define VALOR_POR_DEFECTO_CANTIDAD_BLOQUES 5
#define VALOR_POR_DEFECTO_COORDENADAX 200
#define VALOR_POR_DEFECTO_COORDENADAY 200

void ParserPlataforma::ParsearPlataforma(pugi::xml_node plataforma,Nivel* unNivel,ArchivoLeido* archivoLeido){
	string tipo = plataforma.child_value("tipo");
	int coordenadaX;
	int coordenadaY;
	int cantidadBloques;
	Plataforma* unaPlataforma = new Plataforma();

	try{
		cantidadBloques = stoi(plataforma.child_value("cantidadBloques"));
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de cantidad de bloques enviado no tiene valor valido,se carga el valor por defecto");
		cantidadBloques = VALOR_POR_DEFECTO_CANTIDAD_BLOQUES;
	}

	try{
		coordenadaX = stoi(plataforma.child_value("coordenadaX"));
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de coordenada X enviado no tiene valor valido,se carga el valor por defecto");
		coordenadaX = VALOR_POR_DEFECTO_COORDENADAX;
	}

	try{
		coordenadaY = stoi(plataforma.child_value("coordenadaY"));
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de coordenada Y enviado no tiene valor valido,se carga el valor por defecto");
		coordenadaY = VALOR_POR_DEFECTO_COORDENADAY;
	}

	int coordenadaBloque = coordenadaX;
	for(int i=0;i<cantidadBloques;i++){
		Bloque* unBloque;
		if(tipo.compare("Ladrillo")==0){
			unBloque = new Ladrillo(coordenadaBloque,coordenadaY);
		}else if(tipo.compare("Sorpresa")==0){
			unBloque = new Sorpresa(coordenadaBloque,coordenadaY);
		}
		coordenadaBloque += 40;
		unaPlataforma->agregarBloque(unBloque);
	}
	unNivel->agregarPlataforma(unaPlataforma);
}

