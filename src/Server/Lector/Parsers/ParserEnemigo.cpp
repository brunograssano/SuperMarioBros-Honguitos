#include "ParserEnemigo.hpp"

#include "src/Server/Modelo/Juego/Nivel/Enemigos/Goomba.hpp"
#include "src/Server/Modelo/Juego/Nivel/Enemigos/Koopa.hpp"
#include <map>

#define VALOR_POR_DEFECTO_ENEMIGOS 15
#define VALOR_POR_DEFECTO_COLOR_ENEMIGO 0

bool laCantidadDeLosEnemigosEsInvalida(int cantidad){
    return cantidad < 0;
}

// Color se cuenta desde 0 y la constante desde 1. Por eso el ">="
bool elColorDeGoombaEsInvalido(int color){
    return (color < 0) || (color >= COLORES_GOOMBA_POSIBLES);
}
bool elColorDeKoopaEsInvalido(int color){
    return (color < 0) || (color >= COLORES_KOOPA_POSIBLES);
}

void ParserEnemigo::parsear(pugi::xml_node enemigo, Nivel* unNivel, ArchivoLeido* archivoLeido){
    std::map<std::string, condicionACumplir> mapaTipoColorInvalido;
    mapaTipoColorInvalido["Goomba"] = elColorDeGoombaEsInvalido;
    mapaTipoColorInvalido["Koopa"] = elColorDeKoopaEsInvalido;
    std::string tipo = enemigo.child_value("tipo");
    std::string colorEnemigoString = enemigo.child_value("color");
    std::string cantEnemigosString = enemigo.child_value("cantidad");

    if(tipo!="Goomba" && tipo!="Koopa"){
        archivoLeido->mensajeError.push_back("No existe el tipo de enemigo ("+tipo+"), no se cargara ningun otro tipo de enemigo en su remplazo");
        return;
    }else{
        std::string mensajeCondicion = "El valor de cantidad de enemigos ("+cantEnemigosString+") enviado no tiene valor valido,se carga el valor por defecto";
        int cantidad = intentarObtenerNumero(archivoLeido, cantEnemigosString, laCantidadDeLosEnemigosEsInvalida,
                                             mensajeCondicion, VALOR_POR_DEFECTO_COLOR_ENEMIGO);

        mensajeCondicion = "El valor del color de enemigos ("+colorEnemigoString+") enviado no tiene valor valido,se carga el valor por defecto";
        int colorEnemigoInt = intentarObtenerNumero(archivoLeido, colorEnemigoString, mapaTipoColorInvalido[tipo],
                                                    mensajeCondicion, VALOR_POR_DEFECTO_ENEMIGOS);
        for(int i=0;i<cantidad;i++){
            Enemigo *unEnemigo = nullptr;
            if(tipo=="Goomba"){
                unEnemigo = new Goomba(colorEnemigoInt);
            }else if(tipo=="Koopa"){
                unEnemigo = new Koopa(colorEnemigoInt);
            }
            unNivel->agregarEnemigo(unEnemigo);
        }
    }
}

