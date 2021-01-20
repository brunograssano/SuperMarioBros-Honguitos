#include "Parser.hpp"

int Parser::intentarObtenerNumero(ArchivoLeido* archivoLeido, const string& numeroString, condicionACumplir esValorInvalido, const string& mensajeCondicion, int VALOR_DEFECTO) {
    int numero;
    try{
        numero = stoi(numeroString);
        if(esValorInvalido(numero)){
            archivoLeido->mensajeError.push_back(mensajeCondicion);
            numero = VALOR_DEFECTO;
        }
    }catch(std::exception& e){
        archivoLeido->mensajeError.push_back(mensajeCondicion);
        numero = VALOR_DEFECTO;
    }
    return numero;
}
