#include "ParserNivel.hpp"
#include "ParserTuberia.hpp"

#define VALOR_POR_DEFECTO_MUNDO 1
#define VALOR_POR_DEFECTO_TIEMPO 300
#define VALOR_POR_DEFECTO_MONEDA 30
#define VALOR_POR_DEFECTO_PUNTO_FIN 95
#define MINIMO_PUNTO_BANDERA 50
#define MAXIMO_PUNTO_BANDERA 100
#define TIEMPO_MINIMO 25

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

	auto* unNivel = new Nivel(mundo,direccionFondo,tiempoNivel,cantidadMonedas,puntoBanderaFin);
	archivoLeido->niveles.push_back(unNivel);
	for (pugi::xml_node enemigos: nivel.children("enemigos"))
	{
		for (pugi::xml_node enemigo: enemigos.children("enemigo"))
		{
			auto* parser = new ParserEnemigo();
            parser->parsear(enemigo, unNivel, archivoLeido);
			delete parser;
		}
	}
	for (pugi::xml_node plataformas: nivel.children("plataformas"))
	{
		for (pugi::xml_node plataforma: plataformas.children("plataforma"))
		{
			auto* parser = new ParserPlataforma();
            parser->parsear(plataforma, unNivel, archivoLeido);
			delete parser;
		}
	}

    for (pugi::xml_node tuberia: nivel.children("tuberia"))
    {
        auto* parser = new ParserTuberia();
        parser->parsear(tuberia, unNivel, archivoLeido);
        delete parser;
    }
}
