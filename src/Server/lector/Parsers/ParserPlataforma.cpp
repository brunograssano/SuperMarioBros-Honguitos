#include "ParserPlataforma.hpp"

#define VALOR_POR_DEFECTO_CANTIDAD_BLOQUES 5
#define VALOR_POR_DEFECTO_COORDENADAX 200
#define VALOR_POR_DEFECTO_COORDENADAY 200
#define VALOR_POR_DEFECTO_COLOR 1

void ParserPlataforma::ParsearPlataforma(pugi::xml_node plataforma,Nivel* unNivel,ArchivoLeido* archivoLeido){
	string tipo = plataforma.child_value("tipo");
	string colorBloque = plataforma.child_value("color");

	int coordenadaX,coordenadaY,tipoColorBloque;
	int cantidadBloques;
	Plataforma* unaPlataforma = new Plataforma();

	string cantidadBloquesString = plataforma.child_value("cantidadBloques");
	try{
		cantidadBloques = stoi(cantidadBloquesString);
		if( cantidadBloques < 0){
			archivoLeido->mensajeError.push_back("El valor de cantidad de bloques ("+ cantidadBloquesString +") enviado no tiene valor valido,se carga el valor por defecto");
			cantidadBloques = VALOR_POR_DEFECTO_CANTIDAD_BLOQUES;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.push_back("El valor de cantidad de bloques enviado ("+ cantidadBloquesString +") no tiene valor valido,se carga el valor por defecto");
		cantidadBloques = VALOR_POR_DEFECTO_CANTIDAD_BLOQUES;
	}

	try{
		coordenadaX = stoi(plataforma.child_value("coordenadaX"));
		if(coordenadaX < 0){
			archivoLeido->mensajeError.push_back("El valor de coordenada X enviado no tiene valor valido,se carga el valor por defecto");
			coordenadaX = VALOR_POR_DEFECTO_COORDENADAX;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.push_back("El valor de coordenada X enviado no tiene valor valido,se carga el valor por defecto");
		coordenadaX = VALOR_POR_DEFECTO_COORDENADAX;
	}

	try{
		coordenadaY = stoi(plataforma.child_value("coordenadaY"));
		if(coordenadaY < 0){
			archivoLeido->mensajeError.push_back("El valor de coordenada Y enviado no tiene valor valido,se carga el valor por defecto");
			coordenadaY = VALOR_POR_DEFECTO_COORDENADAY;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.push_back("El valor de coordenada Y enviado no tiene valor valido,se carga el valor por defecto");
		coordenadaY = VALOR_POR_DEFECTO_COORDENADAY;
	}


	if(!colorBloque.empty()){
		try{
				tipoColorBloque = stoi(colorBloque);
				if(tipoColorBloque < 0 || 5 < tipoColorBloque){
					archivoLeido->mensajeError.push_back("El color del bloque "+colorBloque+" no es valido, se carga el por defecto.");
					tipoColorBloque = VALOR_POR_DEFECTO_COLOR;
				}
			}catch(std::exception& e){
				archivoLeido->mensajeError.push_back("El color del bloque "+colorBloque+" no es valido, se carga el por defecto.");
				tipoColorBloque = VALOR_POR_DEFECTO_COLOR;
		}
	}

	int coordenadaBloque = coordenadaX;
	for(int i=0;i<cantidadBloques;i++){
		Bloque* unBloque;
		if(tipo.compare("Ladrillo")==0){
			unBloque = new Ladrillo(coordenadaBloque,coordenadaY, tipoColorBloque);
			coordenadaBloque += 40;
			unaPlataforma->agregarBloque(unBloque);
		}else if(tipo.compare("Sorpresa")==0){
			unBloque = new Sorpresa(coordenadaBloque,coordenadaY);
			coordenadaBloque += 40;
			unaPlataforma->agregarBloque(unBloque);
		}else{
			archivoLeido->mensajeError.push_back("El tipo de bloque no es valido, se pone un ladrillo en su lugar");
			unBloque = new Ladrillo(coordenadaBloque, coordenadaY, VALOR_POR_DEFECTO_COLOR);
			coordenadaBloque += 40;
			unaPlataforma->agregarBloque(unBloque);
		}
	}
	unNivel->agregarPlataforma(unaPlataforma);
}

