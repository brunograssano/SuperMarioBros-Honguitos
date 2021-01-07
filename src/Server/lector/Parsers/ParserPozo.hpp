
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERPOZO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERPOZO_HPP

#include "Parser.h"

class ParserPozo : public Parser{
public:
    void parsear(pugi::xml_node pozo, Nivel* unNivel, ArchivoLeido* archivoLeido) override;
    void parsear(pugi::xml_node nodo,ArchivoLeido* archivoLeido) override{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERPOZO_HPP
