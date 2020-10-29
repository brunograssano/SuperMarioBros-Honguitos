#ifndef SRC_LECTOR_PARSERENEMIGO_HPP_
#define SRC_LECTOR_PARSERENEMIGO_HPP_

using namespace std;
#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "../../modelo/Enemigos/Goomba.hpp"
#include "../../modelo/Enemigos/Koopa.hpp"

class ParserEnemigo{
	public:
			void ParsearEnemigo(pugi::xml_node enemigo,Nivel* unNivel,ArchivoLeido* archivoLeido);
};



#endif /* SRC_LECTOR_PARSERENEMIGO_HPP_ */
