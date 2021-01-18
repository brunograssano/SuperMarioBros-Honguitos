#include "ParserNivel.hpp"
#include "ParserTuberia.hpp"
#include "ParserPozo.hpp"

#define VALOR_POR_DEFECTO_MUNDO 1
#define VALOR_POR_DEFECTO_TIEMPO 300
#define VALOR_POR_DEFECTO_MONEDA 30
#define VALOR_POR_DEFECTO_PUNTO_FIN 95
#define MINIMO_PUNTO_BANDERA 50
#define MAXIMO_PUNTO_BANDERA 100
#define TIEMPO_MINIMO 25
#define FACTOR_PISO 0.1

bool condicionPuntoBandera(int puntoBandera){
    return (puntoBandera < MINIMO_PUNTO_BANDERA) || (puntoBandera > MAXIMO_PUNTO_BANDERA);
}

bool condicionMundo(int mundo){
    return mundo < 0;
}

bool condicionTiempo(int tiempo){
    return tiempo < TIEMPO_MINIMO;
}

bool condicionCantidadMonedas(int cantidadMonedas){
    return cantidadMonedas < 0;
}

void ParserNivel::parsear(pugi::xml_node nivel, ArchivoLeido* archivoLeido){
	string direccionFondo = nivel.child_value("direccionFondo");
    string puntoBanderaFinString = nivel.child_value("puntoBanderaFin");
    string cantMonedasString = nivel.child_value("cantidadMonedas");
    string mundoString = nivel.child_value("mundo");
    string tiempoString = nivel.child_value("tiempoNivel");

    string mensajeCondicion = "El valor de mundo ("+ mundoString +") enviado no tiene valor valido, se carga el valor por defecto";
    int mundo = intentarObtenerNumero(archivoLeido, mundoString,condicionMundo, mensajeCondicion, VALOR_POR_DEFECTO_MUNDO);

    mensajeCondicion = "El valor de tiempo del nivel ("+tiempoString+") enviado no tiene valor valido, se carga el valor por defecto";
    int tiempoNivel = intentarObtenerNumero(archivoLeido, tiempoString,condicionTiempo, mensajeCondicion, VALOR_POR_DEFECTO_TIEMPO);

    mensajeCondicion = "El valor de cantidad de monedas ("+cantMonedasString+") enviado no tiene valor valido, se carga el valor por defecto";
    int cantidadMonedas  = intentarObtenerNumero(archivoLeido, cantMonedasString,condicionCantidadMonedas, mensajeCondicion, VALOR_POR_DEFECTO_MONEDA);

    mensajeCondicion = "El valor de puntoBanderaFin "+ puntoBanderaFinString +" enviado no tiene valor valido, se carga el valor por defecto";
    int puntoBanderaFin = intentarObtenerNumero(archivoLeido, puntoBanderaFinString,condicionPuntoBandera, mensajeCondicion, VALOR_POR_DEFECTO_PUNTO_FIN);

	auto* unNivel = new Nivel(mundo,direccionFondo,tiempoNivel,cantidadMonedas,puntoBanderaFin,(int)((float)archivoLeido->altoVentana*FACTOR_PISO));
	archivoLeido->niveles.push_back(unNivel);
    ParserPlataforma parserPlataforma = ParserPlataforma();
    parsearMultiplesNiveles(nivel, archivoLeido, unNivel, "plataformas", "plataforma",&parserPlataforma);

    ParserEnemigo parserEnemigo = ParserEnemigo();
    parsearMultiplesNiveles(nivel, archivoLeido, unNivel, "enemigos", "enemigo",&parserEnemigo);

    ParserTuberia parserTuberias = ParserTuberia();
    parsearUnNivel(nivel, archivoLeido, unNivel, "tuberia", &parserTuberias);

    ParserPozo parserPozos = ParserPozo();
    parsearUnNivel(nivel, archivoLeido, unNivel, "pozo", &parserPozos);
}

void ParserNivel::parsearUnNivel(const pugi::xml_node &nivel, ArchivoLeido *archivoLeido, Nivel *unNivel, const string& nivelAParsear, Parser *parser) {
    for (pugi::xml_node tuberia: nivel.children(nivelAParsear.c_str())){
        parser->parsear(tuberia, unNivel, archivoLeido);
    }
}

void ParserNivel::parsearMultiplesNiveles(const pugi::xml_node &nivel, ArchivoLeido *archivoLeido, Nivel *unNivel, const string& nivelSuperior, string nivelInferior, Parser* parser) {
    for (pugi::xml_node nodoSuperior: nivel.children(nivelSuperior.c_str())){
        for (pugi::xml_node nodo: nodoSuperior.children(nivelInferior.c_str())){
            parser->parsear(nodo, unNivel, archivoLeido);
        }
    }
}
