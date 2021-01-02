#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERTUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERTUBERIA_HPP

#include <src/Server/modelo/Nivel.hpp>
#include <src/Server/lector/ArchivoLeido.hpp>
#include "../pugixml.hpp"

class ParserTuberia {
    public:
       void parsearTuberia(pugi::xml_node tuberia,Nivel* unNivel,ArchivoLeido* archivoLeido);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PARSERTUBERIA_HPP
