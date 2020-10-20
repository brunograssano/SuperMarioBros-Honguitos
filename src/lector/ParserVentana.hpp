#ifndef SRC_LECTOR_PARSERVENTANA_HPP_
#define SRC_LECTOR_PARSERVENTANA_HPP_

using namespace std;
#include <string>
#include "pugixml.hpp"
#include "ArchivoLeido.hpp"

class ParserVentana{
	public:
			void ParsearVentana(pugi::xml_node ventana,ArchivoLeido* archivoLeido){
				string ancho = ventana.child_value("ancho");
				string alto = ventana.child_value("alto");
				if(ancho.compare("")!=0){
					archivoLeido->anchoVentana = stoi(ancho);
				}
				if(alto.compare("")!=0){
					archivoLeido->altoVentana = stoi(alto);
				}
			 }
};

#endif /* SRC_LECTOR_PARSERVENTANA_HPP_ */
