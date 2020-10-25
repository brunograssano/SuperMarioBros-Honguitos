#include "ParserNivel.hpp"

#define VALOR_POR_DEFECTO_MUNDO 1
#define VALOR_POR_DEFECTO_TIEMPO 300
#define VALOR_POR_DEFECTO_MONEDA 30
#define VALOR_POR_DEFECTO_PUNTO_FIN 2000

void ParserNivel::ParsearNivel(pugi::xml_node nivel,ArchivoLeido* archivoLeido){
	int mundo;
	string direccionFondo = nivel.child_value("direccionFondo");
	int tiempoNivel;
	int cantidadMonedas;
	int puntoBanderaFin;

	try{
		mundo = stoi(nivel.child_value("mundo"));
		if(stoi(nivel.child_value("mundo")) >= 0){
			mundo = stoi(nivel.child_value("mundo"));
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("El valor de mundo enviado no tiene valor valido,se carga el valor por defecto");
			mundo = VALOR_POR_DEFECTO_MUNDO;
		}
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de mundo enviado no tiene valor valido,se carga el valor por defecto");
		mundo = VALOR_POR_DEFECTO_MUNDO;
	}

	try{
		if(stoi(nivel.child_value("tiempoNivel")) >= 0){
			tiempoNivel = stoi(nivel.child_value("tiempoNivel"));
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("El valor de tiempo del nivel enviado no tiene valor valido,se carga el valor por defecto");
			tiempoNivel = VALOR_POR_DEFECTO_TIEMPO;
		}
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de tiempo del nivel enviado no tiene valor valido,se carga el valor por defecto");
		tiempoNivel = VALOR_POR_DEFECTO_TIEMPO;
	}

	try{
		if(stoi(nivel.child_value("cantidadMonedas")) >= 0){
			cantidadMonedas = stoi(nivel.child_value("cantidadMonedas"));
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("El valor de cantidad de monedas enviado no tiene valor valido,se carga el valor por defecto");
			cantidadMonedas = VALOR_POR_DEFECTO_MONEDA;
		}
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de cantidad de monedas enviado no tiene valor valido,se carga el valor por defecto");
		cantidadMonedas = VALOR_POR_DEFECTO_MONEDA;
	}

	try{
		if(stoi(nivel.child_value("puntoBanderaFin")) >= 0){
			puntoBanderaFin = stoi(nivel.child_value("puntoBanderaFin"));
		}else{
			archivoLeido->leidoCorrectamente = false;
			archivoLeido->mensajeError.push_back("El valor de puntoBanderaFin enviado no tiene valor valido,se carga el valor por defecto");
			puntoBanderaFin = VALOR_POR_DEFECTO_PUNTO_FIN;
		}
	}catch(const std::invalid_argument& error){
		archivoLeido->leidoCorrectamente = false;
		archivoLeido->mensajeError.push_back("El valor de puntoBanderaFin enviado no tiene valor valido,se carga el valor por defecto");
		puntoBanderaFin = VALOR_POR_DEFECTO_PUNTO_FIN;
	}


	Nivel* unNivel = new Nivel(mundo,direccionFondo,tiempoNivel,cantidadMonedas,puntoBanderaFin);
	archivoLeido->niveles.push_back(unNivel);
	for (pugi::xml_node enemigos: nivel.children("enemigos"))
	{
		for (pugi::xml_node enemigo: enemigos.children("enemigo"))
		{
			ParserEnemigo* parser = new ParserEnemigo();
			parser->ParsearEnemigo(enemigo,unNivel,archivoLeido);
			delete parser;
		}
	}
	for (pugi::xml_node plataformas: nivel.children("plataformas"))
	{
		for (pugi::xml_node plataforma: plataformas.children("plataforma"))
		{
			ParserPlataforma* parser = new ParserPlataforma();
			parser->ParsearPlataforma(plataforma,unNivel,archivoLeido);
			delete parser;
		}
	}
}
