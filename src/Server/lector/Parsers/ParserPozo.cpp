#include "ParserPozo.hpp"
#include <string>

const int CANTIDAD_TIPOS_POZO = 2, TIPO_POR_DEFECTO_POZO = 0;
const int POS_POR_DEFECTO_POZO = 2500;

bool condicionTipoPozo(int tipo){
    return tipo < 0 || tipo>CANTIDAD_TIPOS_POZO;
}

bool condicionPosicionXPozo(int posX){
    return posX < 0;
}

void ParserPozo::parsear(pugi::xml_node pozo, Nivel* unNivel, ArchivoLeido* archivoLeido) {
    string tipoString = pozo.child_value("tipoPozo");
    string posXString = pozo.child_value("posicionX");

    string mensaje = "El tipo del pozo elegido ("+tipoString+") no tiene valor valido,se carga el valor por defecto";
    int tipo = intentarObtenerNumero(archivoLeido,tipoString,condicionTipoPozo,mensaje,TIPO_POR_DEFECTO_POZO);

    mensaje = "La posicion ingresada de pozo ("+posXString+") no es valida, se asigna por defecto uno";
    int posicionX = intentarObtenerNumero(archivoLeido,posXString,condicionPosicionXPozo,mensaje,POS_POR_DEFECTO_POZO);

    unNivel->agregarPozo(posicionX,tipo);
}