#include "ParserEnemigo.hpp"

#define VALOR_POR_DEFECTO_ENEMIGOS 15

void ParserEnemigo::ParsearEnemigo(pugi::xml_node enemigo,Nivel* unNivel,ArchivoLeido* archivoLeido){
	string tipo = enemigo.child_value("tipo");
	string direccionImagen = enemigo.child_value("direccionImagen");
	int cantidad;

	string cantEnemigosString = enemigo.child_value("cantidad");
	try{
		cantidad = stoi(cantEnemigosString);
		if(cantidad < 0){
			archivoLeido->mensajeError.push_back("El valor de cantidad de enemigos ("+cantEnemigosString+") enviado no tiene valor valido,se carga el valor por defecto");
			cantidad = VALOR_POR_DEFECTO_ENEMIGOS;
		}
	}catch(const std::invalid_argument& error){
		archivoLeido->mensajeError.push_back("El valor de cantidad de enemigos ("+cantEnemigosString+") enviado no tiene valor valido,se carga el valor por defecto");
		cantidad = VALOR_POR_DEFECTO_ENEMIGOS;
	}

	if(tipo.compare("Goomba")!=0 && tipo.compare("Koopa")!=0){
		archivoLeido->mensajeError.push_back("No existe el tipo de enemigo ("+tipo+"), no se cargara ningun otro tipo de enemigo en su remplazo");
	}
	else{
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
}

