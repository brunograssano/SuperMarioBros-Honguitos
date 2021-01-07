#include "ParserTuberia.hpp"
#include <string>

const int CANTIDAD_COLORES_TUBERIAS = 1, COLOR_POR_DEFECTO_TUBERIA = 0, CANTIDAD_TIPOS_TUBERIAS = 1, TIPO_POR_DEFECTO_TUBERIA = 0;
const int POS_POR_DEFECTO_TUBERIA = 2000;

bool condicionColorTuberia(int color){
    return color < 0 || color>CANTIDAD_COLORES_TUBERIAS;
}

bool condicionTipoTuberias(int tipo){
    return tipo < 0 || tipo>CANTIDAD_TIPOS_TUBERIAS;
}

bool condicionPosicionXTuberia(int posX){
    return posX < 0;
}

void ParserTuberia::parsear(pugi::xml_node tuberia, Nivel* unNivel, ArchivoLeido* archivoLeido) {
    string colorString = tuberia.child_value("color");
    string tipoString = tuberia.child_value("tipoTuberia");
    string posXString = tuberia.child_value("posicionX");

    string mensaje = "El color de la tuberia elegido ("+colorString+") no tiene valor valido,se carga el valor por defecto (verde)";
    int color = intentarObtenerNumero(archivoLeido,colorString,condicionColorTuberia,mensaje,COLOR_POR_DEFECTO_TUBERIA);

    mensaje = "El tipo de la tuberia elegido ("+tipoString+") no tiene valor valido,se carga el valor por defecto";
    int tipo = intentarObtenerNumero(archivoLeido,tipoString,condicionTipoTuberias,mensaje,TIPO_POR_DEFECTO_TUBERIA);

    mensaje = "La posicion ingresada de tuberia ("+posXString+") no es valida, se asigna por defecto uno";
    int posicionX = intentarObtenerNumero(archivoLeido,posXString,condicionPosicionXTuberia,mensaje,POS_POR_DEFECTO_TUBERIA);

    unNivel->agregarTuberia(posicionX,tipo,color);
}