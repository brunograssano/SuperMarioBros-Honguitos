#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERTUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERTUBERIA_HPP


#include "Parser.hpp"

class ParserTuberia : public Parser{
    public:
       void parsear(pugi::xml_node tuberia, Nivel* unNivel, ArchivoLeido* archivoLeido) override;
       void parsear(pugi::xml_node nodo,ArchivoLeido* archivoLeido) override{};

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERTUBERIA_HPP
