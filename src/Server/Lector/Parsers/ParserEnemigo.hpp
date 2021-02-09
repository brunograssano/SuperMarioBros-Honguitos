#ifndef SRC_LECTOR_PARSERENEMIGO_HPP_
#define SRC_LECTOR_PARSERENEMIGO_HPP_

#include "Parser.hpp"

class ParserEnemigo : public Parser{
	public:
        void parsear(pugi::xml_node enemigo, Nivel* unNivel, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,ArchivoLeido* archivoLeido) override{};
};




#endif /* SRC_LECTOR_PARSERENEMIGO_HPP_ */
