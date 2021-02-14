#include "ParserPlataforma.hpp"

#include "src/Server/Modelo/Juego/Nivel/Bloques/Ladrillo.hpp"
#include "src/Server/Modelo/Juego/Nivel/Bloques/Sorpresa.hpp"

#define VALOR_POR_DEFECTO_CANTIDAD_BLOQUES 5
#define VALOR_POR_DEFECTO_COORDENADAX 200
#define VALOR_POR_DEFECTO_COORDENADAY 200
#define VALOR_POR_DEFECTO_COLOR 1

const int MAXIMO_ALTO = 4000;

bool seTieneUnaCantidadInvalidaDeBloques(int cantidadBloques){
    return cantidadBloques < 0;
}

bool elBloqueEstaEnUnaPosicionXInvalida(int pos){
    return pos < 0;
}

bool elBloqueEstaEnUnaPosicionYInvalida(int pos){
    return pos < 0 || MAXIMO_ALTO < pos;
}

bool esColorBloqueInvalido(int color){
    return color < 0 || 6 < color;
}

void ParserPlataforma::parsear(pugi::xml_node plataforma, Nivel* unNivel, ArchivoLeido* archivoLeido){
    int tipoColorBloque = 0;
    std::string tipo = plataforma.child_value("tipo");
    std::string colorBloque = plataforma.child_value("color");
    std::string cantidadBloquesString = plataforma.child_value("cantidadBloques");
    std::string posXString = plataforma.child_value("coordenadaX");
    std::string posYString = plataforma.child_value("coordenadaY");

    std::list<Bloque*> unaPlataforma;

    std::string mensajeCondicion = "El valor de cantidad de bloques ("+ cantidadBloquesString +") enviado no tiene valor valido,se carga el valor por defecto";
    int cantidadBloques = intentarObtenerNumero(archivoLeido, cantidadBloquesString,
                                                seTieneUnaCantidadInvalidaDeBloques, mensajeCondicion,
                                                VALOR_POR_DEFECTO_CANTIDAD_BLOQUES);

    mensajeCondicion = "El valor de coordenada X enviado ("+posXString+") no tiene valor valido,se carga el valor por defecto";
    int coordenadaX = intentarObtenerNumero(archivoLeido, posXString, elBloqueEstaEnUnaPosicionXInvalida,
                                            mensajeCondicion, VALOR_POR_DEFECTO_COORDENADAX);

    mensajeCondicion = "El valor de coordenada Y enviado ("+posYString+") no tiene valor valido,se carga el valor por defecto";
    int coordenadaY = intentarObtenerNumero(archivoLeido, posYString, elBloqueEstaEnUnaPosicionYInvalida,
                                            mensajeCondicion, VALOR_POR_DEFECTO_COORDENADAY);

    if(tipo!="Sorpresa"){
        mensajeCondicion = "El color del bloque "+colorBloque+" no es valido, se carga el por defecto.";
        tipoColorBloque = intentarObtenerNumero(archivoLeido, colorBloque, esColorBloqueInvalido, mensajeCondicion,
                                                VALOR_POR_DEFECTO_COLOR);
    }

	for(int i=0;i<cantidadBloques;i++){
		Bloque* unBloque;
		if(tipo=="Ladrillo"){
			unBloque = new Ladrillo(coordenadaX,coordenadaY, tipoColorBloque);
            coordenadaX += 40;
		}else if(tipo=="Sorpresa"){
			unBloque = new Sorpresa(coordenadaX,coordenadaY);
            coordenadaX += 40;
		}else{
			archivoLeido->mensajeError.emplace_back("El tipo de bloque no es valido, se pone un ladrillo en su lugar");
			unBloque = new Ladrillo(coordenadaX, coordenadaY, VALOR_POR_DEFECTO_COLOR);
            coordenadaX += 40;
		}
        unaPlataforma.push_back(unBloque);
	}
	unNivel->agregarPlataforma(unaPlataforma);
}