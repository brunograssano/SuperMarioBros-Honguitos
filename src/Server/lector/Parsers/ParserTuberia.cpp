
#include "ParserTuberia.hpp"
#include <string>


const int CANTIDAD_COLORES_TUBERIAS = 1, COLOR_POR_DEFECTO_TUBERIA = 0, CANTIDAD_TIPOS_TUBERIAS = 1, TIPO_POR_DEFECTO_TUBERIA = 0;
const int POS_POR_DEFECTO_TUBERIA = 2000;

void ParserTuberia::parsearTuberia(pugi::xml_node tuberia, Nivel* unNivel, ArchivoLeido* archivoLeido) {
    string colorString = tuberia.child_value("color");
    string tipoString = tuberia.child_value("tipoTuberia");
    string posXString = tuberia.child_value("posicionX");
    int color,tipo,posicionX;

    try{
        color = stoi(colorString);
        if(color < 0 || color>CANTIDAD_COLORES_TUBERIAS){
            archivoLeido->mensajeError.push_back("El color de la tuberia elegido ("+colorString+") no tiene valor valido,se carga el valor por defecto (verde)");
            color = COLOR_POR_DEFECTO_TUBERIA;
        }
    }catch(std::exception& e){
        archivoLeido->mensajeError.push_back("El color de la tuberia elegido ("+colorString+") no tiene valor valido,se carga el valor por defecto (verde)");
        color = COLOR_POR_DEFECTO_TUBERIA;
    }

    try{
        tipo = stoi(tipoString);
        if(tipo < 0 || tipo>CANTIDAD_TIPOS_TUBERIAS){
            archivoLeido->mensajeError.push_back("El tipo de la tuberia elegido ("+tipoString+") no tiene valor valido,se carga el valor por defecto");
            tipo = TIPO_POR_DEFECTO_TUBERIA;
        }
    }catch(std::exception& e){
        archivoLeido->mensajeError.push_back("El tipo de la tuberia elegido ("+tipoString+") no tiene valor valido,se carga el valor por defecto");
        tipo = TIPO_POR_DEFECTO_TUBERIA;
    }

    try{
        posicionX = stoi(posXString);
    }catch(std::exception& e){
        archivoLeido->mensajeError.push_back("La posicion ingresada de tuberia ("+posXString+") no es valida, se asigna por defecto uno");
        posicionX = POS_POR_DEFECTO_TUBERIA;
    }

    unNivel->agregarTuberia(posicionX,tipo,color);
}