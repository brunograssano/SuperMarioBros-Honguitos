#include "ParserNivel.hpp"

void ParserNivel::ParsearNivel(pugi::xml_node nivel,ArchivoLeido* archivoLeido){
	string mundo = nivel.child_value("mundo");
	string direccionFondo = nivel.child_value("direccionFondo");
	string tiempoNivel = nivel.child_value("tiempoNivel");
	string cantidadMonedas = nivel.child_value("cantidadMonedas");
	if(mundo.compare("")==0 || tiempoNivel.compare("")==0 || cantidadMonedas.compare("")==0){
		return;
	}
	Nivel* unNivel = new Nivel(stoi(mundo),direccionFondo,stoi(tiempoNivel),stoi(cantidadMonedas));
	archivoLeido->niveles.push_back(unNivel);
	for (pugi::xml_node enemigos: nivel.children("enemigos"))
	{
		for (pugi::xml_node enemigo: enemigos.children("enemigo"))
		{
			ParserEnemigo* parser = new ParserEnemigo();
			parser->ParsearEnemigo(enemigo,unNivel);
			delete parser;
		}
	}
	for (pugi::xml_node plataformas: nivel.children("plataformas"))
	{
		for (pugi::xml_node plataforma: plataformas.children("plataforma"))
		{
			ParserPlataforma* parser = new ParserPlataforma();
			parser->ParsearPlataforma(plataforma,unNivel);
			delete parser;
		}
	}
}
