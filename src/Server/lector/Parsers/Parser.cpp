#include "Parser.hpp"

int Parser::intentarObtenerNumero(ArchivoLeido* archivoLeido,string numeroString, condicionACumplir condicion,string mensajeCondicion,int VALOR_DEFECTO) {
    int numero;
    try{
        numero = stoi(numeroString);
        if(condicion(numero)){
            archivoLeido->mensajeError.push_back(mensajeCondicion);
            numero = VALOR_DEFECTO;
        }
    }catch(std::exception& e){
        archivoLeido->mensajeError.push_back(mensajeCondicion);
        numero = VALOR_DEFECTO;
    }
    return numero;
}
