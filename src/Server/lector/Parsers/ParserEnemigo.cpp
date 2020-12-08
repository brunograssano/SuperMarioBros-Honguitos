#include "ParserEnemigo.hpp"

#define VALOR_POR_DEFECTO_ENEMIGOS 15
#define VALOR_POR_DEFECTO_COLOR_ENEMIGO 0

void ParserEnemigo::ParsearEnemigo(pugi::xml_node enemigo,Nivel* unNivel,ArchivoLeido* archivoLeido){
	string tipo = enemigo.child_value("tipo");
	string colorEnemigoString = enemigo.child_value("color");

	int cantidad, colorEnemigoInt;

	string cantEnemigosString = enemigo.child_value("cantidad");
	try{
		cantidad = stoi(cantEnemigosString);
		if(cantidad < 0){
			archivoLeido->mensajeError.push_back("El valor de cantidad de enemigos ("+cantEnemigosString+") enviado no tiene valor valido,se carga el valor por defecto");
			cantidad = VALOR_POR_DEFECTO_ENEMIGOS;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.push_back("El valor de cantidad de enemigos ("+cantEnemigosString+") enviado no tiene valor valido,se carga el valor por defecto");
		cantidad = VALOR_POR_DEFECTO_ENEMIGOS;
	}

	try{
		colorEnemigoInt = stoi(colorEnemigoString);
		if((colorEnemigoInt < 0) || (colorEnemigoInt>3)){
			archivoLeido->mensajeError.push_back("El valor del color de enemigos ("+colorEnemigoString+") enviado no tiene valor valido,se carga el valor por defecto");
			colorEnemigoInt = VALOR_POR_DEFECTO_COLOR_ENEMIGO;
		}
		}catch(std::exception& e){
			archivoLeido->mensajeError.push_back("El valor del color de enemigos ("+colorEnemigoString+") enviado no tiene valor valido,se carga el valor por defecto");
			colorEnemigoInt = VALOR_POR_DEFECTO_COLOR_ENEMIGO;
		}

	if(tipo.compare("Goomba")!=0 && tipo.compare("Koopa")!=0){
		archivoLeido->mensajeError.push_back("No existe el tipo de enemigo ("+tipo+"), no se cargara ningun otro tipo de enemigo en su remplazo");
	}
	else{
		for(int i=0;i<cantidad;i++){
				Enemigo* unEnemigo;
				if(tipo.compare("Goomba")==0){
					unEnemigo = new Goomba(colorEnemigoInt);
				}else if(tipo.compare("Koopa")==0){
					unEnemigo = new Koopa(colorEnemigoInt);
				}
				unNivel->agregarEnemigo(unEnemigo);
		}
	}
}

