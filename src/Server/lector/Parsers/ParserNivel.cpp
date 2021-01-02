#include "ParserNivel.hpp"
#include "ParserTuberia.hpp"

#define VALOR_POR_DEFECTO_MUNDO 1
#define VALOR_POR_DEFECTO_TIEMPO 300
#define VALOR_POR_DEFECTO_MONEDA 30
#define VALOR_POR_DEFECTO_PUNTO_FIN 95
#define MINIMO_PUNTO_BANDERA 50
#define MAXIMO_PUNTO_BANDERA 100

void ParserNivel::ParsearNivel(pugi::xml_node nivel,ArchivoLeido* archivoLeido){
	int mundo;
	string direccionFondo = nivel.child_value("direccionFondo");
	int tiempoNivel;
	int cantidadMonedas;
	int puntoBanderaFin;

	try{
		string mundoString = nivel.child_value("mundo");
		mundo = stoi(mundoString);
		if(mundo < 0){
			archivoLeido->mensajeError.push_back("El valor de mundo ("+ mundoString +") enviado no tiene valor valido, se carga el valor por defecto");
			mundo = VALOR_POR_DEFECTO_MUNDO;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.emplace_back("El valor de mundo enviado no tiene valor valido, se carga el valor por defecto");
		mundo = VALOR_POR_DEFECTO_MUNDO;
	}

	try{
		string tiempoString = nivel.child_value("tiempoNivel");
		tiempoNivel = stoi(tiempoString);
		if(stoi(nivel.child_value("tiempoNivel")) < 0){
			archivoLeido->mensajeError.push_back("El valor de tiempo del nivel ("+tiempoString+") enviado no tiene valor valido, se carga el valor por defecto");
			tiempoNivel = VALOR_POR_DEFECTO_TIEMPO;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.emplace_back("El valor de tiempo del nivel enviado no tiene valor valido, se carga el valor por defecto");
		tiempoNivel = VALOR_POR_DEFECTO_TIEMPO;
	}

	string cantMonedasString = nivel.child_value("cantidadMonedas");
	try{
		cantidadMonedas = stoi(cantMonedasString);
		if(cantidadMonedas < 0){
			archivoLeido->mensajeError.push_back("El valor de cantidad de monedas ("+cantMonedasString+") enviado no tiene valor valido, se carga el valor por defecto");
			cantidadMonedas = VALOR_POR_DEFECTO_MONEDA;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.push_back("El valor de cantidad de monedas ("+cantMonedasString+") enviado no tiene valor valido, se carga el valor por defecto");
		cantidadMonedas = VALOR_POR_DEFECTO_MONEDA;
	}

	try{
		string puntoBanderaFinString = nivel.child_value("puntoBanderaFin");
		puntoBanderaFin = stoi(puntoBanderaFinString);
		if(puntoBanderaFin < MINIMO_PUNTO_BANDERA || puntoBanderaFin > MAXIMO_PUNTO_BANDERA){
			archivoLeido->mensajeError.push_back("El valor de puntoBanderaFin "+ puntoBanderaFinString +" enviado no tiene valor valido, se carga el valor por defecto");
			puntoBanderaFin = VALOR_POR_DEFECTO_PUNTO_FIN;
		}
	}catch(std::exception& e){
		archivoLeido->mensajeError.emplace_back("El valor de puntoBanderaFin enviado no tiene valor valido, se carga el valor por defecto");
		puntoBanderaFin = VALOR_POR_DEFECTO_PUNTO_FIN;
	}

	auto* unNivel = new Nivel(mundo,direccionFondo,tiempoNivel,cantidadMonedas,puntoBanderaFin);
	archivoLeido->niveles.push_back(unNivel);
	for (pugi::xml_node enemigos: nivel.children("enemigos"))
	{
		for (pugi::xml_node enemigo: enemigos.children("enemigo"))
		{
			auto* parser = new ParserEnemigo();
			parser->ParsearEnemigo(enemigo,unNivel,archivoLeido);
			delete parser;
		}
	}
	for (pugi::xml_node plataformas: nivel.children("plataformas"))
	{
		for (pugi::xml_node plataforma: plataformas.children("plataforma"))
		{
			auto* parser = new ParserPlataforma();
			parser->ParsearPlataforma(plataforma,unNivel,archivoLeido);
			delete parser;
		}
	}

    for (pugi::xml_node tuberia: nivel.children("tuberia"))
    {
        auto* parser = new ParserTuberia();
        parser->parsearTuberia(tuberia,unNivel,archivoLeido);
        delete parser;
    }
}
