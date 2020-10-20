#ifndef SRC_LECTOR_PARSERENEMIGO_HPP_
#define SRC_LECTOR_PARSERENEMIGO_HPP_

using namespace std;
#include <string>
#include "pugixml.hpp"
#include "ArchivoLeido.hpp"
#include "../modelo/Enemigos/Goomba.h"
#include "../modelo/Enemigos/Koopa.h"

class ParserEnemigo{
	public:
			void ParsearEnemigo(pugi::xml_node enemigo,Nivel* unNivel){
				string tipo = enemigo.child_value("tipo");
				string direccionImagen = enemigo.child_value("direccionImagen");
				string cantidad = enemigo.child_value("cantidad");
				if(cantidad.compare("") == 0){
					return;
				}
				for(int i=0;i<stoi(cantidad);i++){
					Enemigo* unEnemigo;
					if(tipo.compare("Goomba")==0){
						unEnemigo = new Goomba(direccionImagen);
					}else if(tipo.compare("Koopa")==0){
						unEnemigo = new Koopa(direccionImagen);
					}
					unNivel->agregarEnemigo(unEnemigo);
				}
			 }
};



#endif /* SRC_LECTOR_PARSERENEMIGO_HPP_ */
