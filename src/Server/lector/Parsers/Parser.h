#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PARSER_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PARSER_H

#include "../pugixml.hpp"
#include <src/Server/lector/ArchivoLeido.hpp>

typedef bool (*condicionACumplir)(int);


class Parser {
    public:
        virtual ~Parser() {};
        virtual void parsear(pugi::xml_node nodo,ArchivoLeido* archivoLeido) = 0;
        virtual void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido) = 0;

    protected:

    int intentarObtenerNumero(ArchivoLeido *archivoLeido, string numeroString, condicionACumplir condicion,
                                string mensajeCondicion, int VALOR_DEFECTO);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PARSER_H
