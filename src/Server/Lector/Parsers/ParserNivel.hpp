#ifndef SRC_LECTOR_PARSERNIVEL_HPP_
#define SRC_LECTOR_PARSERNIVEL_HPP_

#include <string>
#include "../pugixml.hpp"
#include "../ArchivoLeido.hpp"
#include "ParserEnemigo.hpp"
#include "ParserPlataforma.hpp"

class ParserNivel : public Parser{
	public:
		void parsear(pugi::xml_node nivel, ArchivoLeido* archivoLeido) override;
        void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido)override{};

    private:
        static void parsearMultiplesNiveles(const pugi::xml_node &nivel, ArchivoLeido *archivoLeido, Nivel *unNivel,
                            const std::string& nivelSuperior,
                            std::string nivelInferior, Parser* parser) ;

        static void parsearUnNivel(const pugi::xml_node &nivel, ArchivoLeido *archivoLeido, Nivel *unNivel, const std::string& nivelAParsear,
                        Parser *parser) ;
};


#endif /* SRC_LECTOR_PARSERNIVEL_HPP_ */
