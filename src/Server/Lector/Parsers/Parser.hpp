#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_PARSER_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_PARSER_HPP

#include "../pugixml.hpp"
#include "src/Server/Lector/ArchivoLeido.hpp"

typedef bool (*condicionACumplir)(int);


class Parser {
    public:
        virtual ~Parser() = default;
        virtual void parsear(pugi::xml_node nodo,ArchivoLeido* archivoLeido) = 0;
        virtual void parsear(pugi::xml_node nodo,Nivel* unNivel,ArchivoLeido* archivoLeido) = 0;

    protected:

    static int intentarObtenerNumero(ArchivoLeido *archivoLeido, const std::string& numeroString, condicionACumplir esValorInvalido,
                                const std::string& mensajeCondicion, int VALOR_DEFECTO);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_PARSER_HPP
