#include "ParserEnemigo.hpp"

#define VALOR_POR_DEFECTO_ENEMIGOS 15
#define VALOR_POR_DEFECTO_COLOR_ENEMIGO 0

bool condicionCantidadEnemigos(int cantidad){
    return cantidad < 0;
}

bool condicionColorEnemigos(int color){
    return (color < 0) || (color>3);
}

void ParserEnemigo::parsear(pugi::xml_node enemigo, Nivel* unNivel, ArchivoLeido* archivoLeido){
	string tipo = enemigo.child_value("tipo");
	string colorEnemigoString = enemigo.child_value("color");
    string cantEnemigosString = enemigo.child_value("cantidad");

    string mensajeCondicion = "El valor de cantidad de enemigos ("+cantEnemigosString+") enviado no tiene valor valido,se carga el valor por defecto";
	int cantidad = intentarObtenerNumero(archivoLeido, cantEnemigosString,condicionCantidadEnemigos, mensajeCondicion, VALOR_POR_DEFECTO_COLOR_ENEMIGO);

	mensajeCondicion = "El valor del color de enemigos ("+colorEnemigoString+") enviado no tiene valor valido,se carga el valor por defecto";
    int colorEnemigoInt = intentarObtenerNumero(archivoLeido, colorEnemigoString,condicionColorEnemigos, mensajeCondicion, VALOR_POR_DEFECTO_ENEMIGOS);


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

