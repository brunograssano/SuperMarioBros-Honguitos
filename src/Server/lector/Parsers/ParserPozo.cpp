#include "ParserPozo.hpp"
#include <string>

const int CANTIDAD_TIPOS_POZO = 2, TIPO_POR_DEFECTO_POZO = 0,CANTIDAD_FONDOS_POZO = 4;
const int POS_POR_DEFECTO_POZO = 2500;
#define FONDO_POR_DEFECTO 0

bool condicionTipoPozo(int tipo){
    return tipo < 0 || tipo>CANTIDAD_TIPOS_POZO;
}

bool condicionPosicionXPozo(int posX){
    return posX < 0;
}

bool condicionFondoPozo(int fondo){
    return fondo < 0 || fondo>CANTIDAD_FONDOS_POZO;
}

void ParserPozo::parsear(pugi::xml_node pozo, Nivel* unNivel, ArchivoLeido* archivoLeido) {
    string tipoString = pozo.child_value("tipoPozo");
    string posXString = pozo.child_value("posicionX");
    string fondoString = pozo.child_value("fondoPozo");

    string mensaje = "El tipo del pozo elegido ("+tipoString+") no tiene valor valido,se carga el valor por defecto";
    int tipo = intentarObtenerNumero(archivoLeido,tipoString,condicionTipoPozo,mensaje,TIPO_POR_DEFECTO_POZO);

    mensaje = "La posicion ingresada de pozo ("+posXString+") no es valida, se asigna por defecto uno";
    int posicionX = intentarObtenerNumero(archivoLeido,posXString,condicionPosicionXPozo,mensaje,POS_POR_DEFECTO_POZO);

    mensaje = "El fondo del pozo ("+fondoString+") no es valido, se asigna por defecto uno";
    int fondo = intentarObtenerNumero(archivoLeido,fondoString,condicionFondoPozo,mensaje,FONDO_POR_DEFECTO);

    unNivel->agregarPozo(posicionX, tipo, fondo);
}