#include "ParserEnemigo.hpp"

#define VALOR_POR_DEFECTO_ENEMIGOS 15

void ParserEnemigo::ParsearEnemigo(pugi::xml_node enemigo,Nivel* unNivel,ArchivoLeido* archivoLeido){
	string tipo = enemigo.child_value("tipo");
	string direccionImagen = enemigo.child_value("direccionImagen");
	int cantidad;

	try{
		if(stoi(enemigo.child_value("cantidad")) >= 0){
			cantidad = stoi(enemigo.child_value("cantidad"));
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("El valor de cantidad de enemigos enviado no tiene valor valido,se carga el valor por defecto");
			cantidad = VALOR_POR_DEFECTO_ENEMIGOS;
		}
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de cantidad de enemigos enviado no tiene valor valido,se carga el valor por defecto");
		cantidad = VALOR_POR_DEFECTO_ENEMIGOS;
	}

	for(int i=0;i<cantidad;i++){
		Enemigo* unEnemigo;
		if(tipo.compare("Goomba")==0){
			unEnemigo = new Goomba(direccionImagen);
		}else if(tipo.compare("Koopa")==0){
			unEnemigo = new Koopa(direccionImagen);
		}
		unNivel->agregarEnemigo(unEnemigo);
	}
}

