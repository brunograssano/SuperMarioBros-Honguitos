#include "ParserVentana.hpp"
#define VALOR_POR_DEFECTO_ANCHO 800
#define VALOR_POR_DEFECTO_ALTO 600

bool elAnchoEsInvalido(int ancho){
    return ancho<VALOR_POR_DEFECTO_ANCHO;
}

bool elAltoEsInvalido(int alto){
    return alto<VALOR_POR_DEFECTO_ALTO;
}

void ParserVentana::parsear(pugi::xml_node ventana, ArchivoLeido* archivoLeido){
    std::string ancho = ventana.child_value("ancho");
    std::string alto = ventana.child_value("alto");

    std::string mensaje = "El valor de ancho ("+ancho+") enviado no tiene valor valido,se carga el valor por defecto";
    archivoLeido->anchoVentana = intentarObtenerNumero(archivoLeido, ancho, elAnchoEsInvalido, mensaje,
                                                       VALOR_POR_DEFECTO_ANCHO);

    mensaje = "El valor de alto ("+alto+") enviado no tiene valor valido,se carga el valor por defecto";
    archivoLeido->altoVentana = intentarObtenerNumero(archivoLeido, alto, elAltoEsInvalido, mensaje,
                                                      VALOR_POR_DEFECTO_ALTO);
}

