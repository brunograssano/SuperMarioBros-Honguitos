#include "Lector.h"
#include "pugixml.hpp"
#include <string>
#include <iostream>
#include "ArchivoLeido.hpp"
#include "../log/Error.h"
#include "../log/Debug.h"
#include "../log/Info.h"
#include "../modelo/Nivel.h"
#include "../modelo/Enemigos/Goomba.h"
#include "../modelo/Enemigos/Koopa.h"
using namespace std;

ArchivoLeido* Lector::leerArchivo(string nombreArchivo){
	ArchivoLeido* archivoLeido = new ArchivoLeido();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(nombreArchivo.c_str());
	if (!result){
		return NULL;
	}

    for (pugi::xml_node log: doc.child("configuracion").children("log"))
    {
    	string level = log.child_value("level");
    	if(level.compare("ERROR") == 0){
    		archivoLeido->tipoLog = new Error();
    	}else if(level.compare("DEBUG") == 0){
    		archivoLeido->tipoLog = new Debug();
    	}else if(level.compare("INFO") == 0){
    		archivoLeido->tipoLog = new Info();
    	}

    }

    for (pugi::xml_node ventana: doc.child("configuracion").children("ventana"))
    {
    	string ancho = ventana.child_value("ancho");
    	string alto = ventana.child_value("alto");
    	archivoLeido->anchoVentana = stoi(ancho);
    	archivoLeido->altoVentana = stoi(alto);
    }

    for (pugi::xml_node niveles: doc.child("configuracion").children("niveles"))
    {
    	for (pugi::xml_node nivel: niveles.children("nivel"))
    	{
    		string mundo = nivel.child_value("mundo");
    		string direccionFondo = nivel.child_value("direccionFondo");
    		string tiempoNivel = nivel.child_value("tiempoNivel");
    		string cantidadMonedas = nivel.child_value("cantidadMonedas");
    		Nivel* unNivel = new Nivel(stoi(mundo),direccionFondo,stoi(tiempoNivel),stoi(cantidadMonedas));
    		archivoLeido->niveles.push_back(unNivel);

    		for (pugi::xml_node enemigos: nivel.children("enemigos"))
    		{
    			for (pugi::xml_node enemigo: enemigos.children("enemigo"))
    			{
					string tipo = enemigo.child_value("tipo");
					string direccionImagen = enemigo.child_value("direccionImagen");
					string cantidad = enemigo.child_value("cantidad");
					for(int i=0;i<stoi(cantidad);i++){
						Enemigo* unEnemigo;
						if(tipo.compare("Goomba")==0){
							unEnemigo = new Goomba(direccionImagen);
						}else if(tipo.compare("Koopa")==0){
							unEnemigo = new Koopa(direccionImagen);
						}
						unNivel->agregarEnemigo(unEnemigo);
					}
    			}
    		}
    		for (pugi::xml_node plataformas: nivel.children("plataformas"))
			{
				for (pugi::xml_node plataforma: plataformas.children("plataforma"))
				{
					string tipo = plataforma.child_value("tipo");
					string coordenadaX = plataforma.child_value("coordenadaX");
					string coordenadaY = plataforma.child_value("coordenadaY");
					string cantidadBloques = plataforma.child_value("cantidadBloques");
					Plataforma* unaPlataforma = new Plataforma();
					int coordenadaBloque = stoi(coordenadaX);
					for(int i=0;i<stoi(cantidadBloques);i++){
						Bloque* unBloque;
						if(tipo.compare("Ladrillo")==0){
							unBloque = new Ladrillo(coordenadaBloque,stoi(coordenadaY));
						}else if(tipo.compare("Sorpresa")==0){
							unBloque = new Sorpresa(coordenadaBloque,stoi(coordenadaY));
						}
						coordenadaBloque += 50;
						unaPlataforma->agregarBloque(unBloque);
					}
					unNivel->agregarPlataforma(unaPlataforma);
				}
			}
    	}
    }
    return archivoLeido;
}


