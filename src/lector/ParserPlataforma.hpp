#ifndef SRC_LECTOR_PARSERPLATAFORMA_HPP_
#define SRC_LECTOR_PARSERPLATAFORMA_HPP_

using namespace std;
#include <string>
#include "pugixml.hpp"
#include "ArchivoLeido.hpp"

class ParserPlataforma{
	public:
			void ParsearPlataforma(pugi::xml_node plataforma,Nivel* unNivel){
				string tipo = plataforma.child_value("tipo");
				string coordenadaX = plataforma.child_value("coordenadaX");
				string coordenadaY = plataforma.child_value("coordenadaY");
				string cantidadBloques = plataforma.child_value("cantidadBloques");
				Plataforma* unaPlataforma = new Plataforma();
				if(coordenadaX.compare("")==0 || coordenadaY.compare("")==0 || cantidadBloques.compare("")==0){
					return;
				}
				int coordenadaBloque = stoi(coordenadaX);
				for(int i=0;i<stoi(cantidadBloques);i++){
					Bloque* unBloque;
					if(tipo.compare("Ladrillo")==0){
						unBloque = new Ladrillo(coordenadaBloque,stoi(coordenadaY));
					}else if(tipo.compare("Sorpresa")==0){
						unBloque = new Sorpresa(coordenadaBloque,stoi(coordenadaY));
					}
					coordenadaBloque += 50;
					unaPlataforma->agregarBloque(unBloque);
				}
				unNivel->agregarPlataforma(unaPlataforma);
			 }
};




#endif /* SRC_LECTOR_PARSERPLATAFORMA_HPP_ */
